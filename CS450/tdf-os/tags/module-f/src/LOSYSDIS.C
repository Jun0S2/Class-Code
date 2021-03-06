
// LOSYSDIS.C
// Responsible for dispatching and running all of the processes
// in the ready queue.
//
// tours de force http://ducksarepeople.com/tdf

#include <stdio.h>
#include <dos.h>
#include "mpx_supt.h"
#include "tdf.h"
#include "losysdis.h"
#include "pcb.h"
#include "tdfdrive.h"
#include "trmdrive.h"

extern PCBDLL** PRIORITY_QUEUES;
unsigned short ss_save;
unsigned short sp_save;
unsigned short new_ss;
unsigned short new_sp;
extern context *context_p;
extern params *params_p;
PCB* l_cop;
int INT_ERR;
int l_err;
unsigned short tmp_stack[1025];

IOD *iod_tmp;

IOCB *iocb_com;
IOCB *iocb_term;

void dispatch_init(){
  // Initialize the interrupt vector for SYS_CALL
  INT_ERR = sys_set_vec(sys_call);

  l_cop = NULL;

  ss_save = NULL;
  sp_save = NULL;

  // Also, initialize the IOCBs for com port and terminal driver. These
  // are essentially the queues for the IODs. Initialize the integer values
  // in each to be 0.
  iocb_com = sys_alloc_mem(sizeof(IOCB));
  iocb_com->count = 0;
  iocb_com->event_flag = 0;
  iocb_term = sys_alloc_mem(sizeof(IOCB));
  iocb_term->count = 0;
  iocb_term->event_flag = 0;

  // Open device drivers. In TESTCOMR.C, the second parameter of com_open
  // is 1200, so let's do that too.
  trm_open( &iocb_term->event_flag);
  com_open( &iocb_com->event_flag, 1200);
}

void interrupt dispatch(){
  //If sp_save is null
  //Save current SS and SP
  if( sp_save == NULL ){
    ss_save = _SS;
    sp_save = _SP;
  }

  if( givemeready() != NULL ){ //Found it
    l_cop = givemeready();
    //Remove from ready queue, set state to RUNNING
    //    l_err = pready_to_running();
    PCB_remove( l_cop );
    l_cop->state = RUNNING;
    //Set _SS and _SP to the cop’s stack (context switch)
    new_ss = FP_SEG(l_cop->pstack_top);
    new_sp = FP_OFF(l_cop->pstack_top);
    _SS = new_ss;
    _SP = new_sp;
  }
  else {
    //Set COP to NULL
    l_cop = NULL;
    //Restore SS and SP
    _SS = ss_save;
    _SP = sp_save;
    //Set sp_save & ss_save = null;
    ss_save = NULL;
    sp_save = NULL;
  }
  //end
}

void interrupt sys_call() {
  // MPX_SUPT.H defines numerous OP_CODEs, including:
  /*
   * IDLE    0; READ    1; WRITE   2
   * CLEAR   3; GOTOXY  4; EXIT    5
   */

  // First we need to switch the system (temporary) stack and set the COP
  new_ss = FP_OFF(&tmp_stack);
  new_sp = FP_OFF(&tmp_stack);
  l_cop->pstack_top = MK_FP(_SS, _SP);

  // Call trm_getc() - this will flush the DOS keyboard into MPX buffer
  trm_getc( );

  // Check com port, if it is 1 then we may proceed with clearing the event
  // flag, unblock the process, free the IOD, proceeding to the next in queue,
  // and try to process it.
  if ( iocb_com->event_flag == 1 ) {
    iocb_com->event_flag = 0;
    iod_tmp = iocb_com->head;
    iocb_com->head = (iocb_com->head)->next;
    punblock((iod_tmp->pcb)->name);
    sys_free_mem(iod_tmp);         
    if ( iocb_com->head != NULL ) {
      switch ( (iocb_com->head)->type ) {
      case READ:
        com_read((iocb_com->head)->transfer_buffer, (iocb_com->head)->count);
        break;
      case WRITE:
        com_write((iocb_com->head)->transfer_buffer, (iocb_com->head)->count);
        break;
      default:
        break;
      }
    }
    iocb_com->count = iocb_com->count - 1;
  }

  // Check term port, if it is 1 then we may proceed with clearing the event
  // flag, unblock the process, free the IOD, proceeding to the next in queue,
  // and try to process it.
  if ( iocb_term->event_flag == 1 ) {
    iocb_term->event_flag = 0;
    iod_tmp = iocb_term->head;
    iocb_term->head = (iocb_term->head)->next;
    punblock((iod_tmp->pcb)->name);
    sys_free_mem(iod_tmp);                     
    if ( iocb_term->head != NULL ) {
      switch ( (iocb_term->head)->type ) {
      case READ:
	trm_read((iocb_term->head)->transfer_buffer, (iocb_term->head)->count);
	break;
      case WRITE:
	trm_write((iocb_term->head)->transfer_buffer, (iocb_term->head)->count);
	break;
      case CLEAR:
	trm_clear();
	break;
      case GOTOXY:
	trm_gotoxy( 0, 0 );
	break;
      default:
	break;
      }
    }
    iocb_term->count = iocb_term->count - 1;
  }
  
  // Here do our old routine with some jazz hands, except add more checks
  // for READ, WRITE, CLEAR, and GOTOXY.
  params_p = (params*)(l_cop->pstack_top + sizeof(context));
  switch(params_p->op_code) {
  case IDLE:
    PCB_insert( PRIORITY_QUEUES[READY], l_cop, READY );
    break;
  case EXIT:
    PCB_free( l_cop );
    break;
  case READ:
    IO_scheduler( );
    break;
  case WRITE:
    IO_scheduler( );
    break;
  case CLEAR:
    IO_scheduler( );
    break;
  case GOTOXY:
    IO_scheduler( );
    break;
  default:
    break;
  }

  dispatch( );
}

void IO_scheduler () {
  int dev_id;
  IOD *iod;

// Check which device is being requested (stored in the device_id of the 
// parameters)
  dev_id = params_p->device_id;
  
// Create an IOD for the new request (allocate space using sys_alloc_mem)
  iod = sys_alloc_mem(sizeof(IOD));

// Set the PCB*  in the IOD to COP, and set the name-> The COP is the process 
// making the I/O request, so you need to save that in the IOD
  iod->pcb = l_cop;

// Set the buffer address to the parameter* buf_addr, and count address 
// to the parameter* count_addr, and the request to the parameter* op_code
  iod->transfer_buffer = params_p->buff_addr;
  iod->count = params_p->count_addr;
  iod->type = params_p->op_code;

// If the waiting queue for that device is empty (count = 0)
// Insert the new IOD into the waiting queue as the head and tail, set 
// count = 1. Process the request immediately.
//
// If waiting queue for that device is not empty, Insert the new IOD into 
// the waiting queue at the tail. 
//
// Block the process.
  switch (dev_id) {
  case TERMINAL:
    switch (iocb_term->count) {
    case 0:
      iocb_term->head = iod;
      iocb_term->tail = iod;
      iocb_term->count = 1;
      switch( iod->type ) {
      case READ:
	trm_read( iod->transfer_buffer, iod->count );
	break;
      case WRITE:
	trm_write( iod->transfer_buffer, iod->count );
	break;
      case CLEAR:
	trm_clear( );
	break;
      case GOTOXY:
	trm_gotoxy( 0, 0 );
	break;
      default:
	break;
      }
      break;
    default:
      (iocb_term->tail)->next = iod;
      iocb_term->tail = iod;
      iocb_term->count = iocb_term->count + 1;
      break;
    }
    PCB_insert( PRIORITY_QUEUES[BLOCKED], iod->pcb, BLOCKED );
    break;
  case COM_PORT:
    switch (iocb_com->count) {
    case 0:
      iocb_com->head = iod;
      iocb_com->tail = iod;
      iocb_com->count = 1;
      switch( iod->type ) {
      case READ:
	com_read( iod->transfer_buffer, iod->count );
	break;
      case WRITE:
	com_write( iod->transfer_buffer, iod->count );
	break;
      default:
	break;
      }
      break;
    default:
      (iocb_com->tail)->next = iod;
      iocb_com->tail = iod;
      iocb_com->count = iocb_com->count + 1;
      break;
    }
    PCB_insert( PRIORITY_QUEUES[BLOCKED], iod->pcb, BLOCKED );
    break;
  default:
    break;
  }

// Return.
  return;
}

