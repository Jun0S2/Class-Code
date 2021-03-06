
// PCBMAN.C
// This file contains the commands needed to manage Process Control Blocks.
//
// *****THE FOLLOWING IS DEFINED IN PCB.H***** 
// Be advised, you are given access to PRIORITY_QUEUES[0-3]
// READY 0
// BLOCKED 1
// READYSUSPENDED 2
// BLOCKEDSUSPENDED 3
//
// Process classes:
// APPLICATION 0
// SYSTEM 1
//
// tours de force: http://www.ducksarepeople.com/tdf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpx_supt.h"
#include "pcb.h"

int pblock(char *name, PCBDLL **PRIORITY_QUEUES){
  PCB *temp;
  PCB *newpcb;
  int PCB_BLOCK_ERR = 0;
  int priority, pclass, state;
  // stack wtf
  // int memsize;
  // unsigned char *load;
  // unsigned char *exec;

  temp = PCB_find(name, PRIORITY_QUEUES);
  if( temp == NULL ){
    printf("Could not find the specified Process Control Block.\n");
    return PCB_BLOCK_ERR;
  }
  else {
    
    // Grab the temp values...
    priority = temp->priority;
    pclass = temp->pclass;
    state = temp->state;
    //memsize = temp->memsize;
    //load = temp->load;
    //exec = temp->exec;
    
    // Now remove the PCB
    PCB_remove(temp, PRIORITY_QUEUES);
    
    // Now make a new one
    newpcb = PCB_setup(name, priority, pclass, PRIORITY_QUEUES);

    // Stick it in the right place
    if( state == 0 ){
      PCB_BLOCK_ERR = PCB_insert(PRIORITY_QUEUES[BLOCKED], newpcb, BLOCKED);
      printf("Changing state of %s to BLOCKED.\n", name);
    }
    else if( state == 1 ){
      PCB_BLOCK_ERR = PCB_insert(PRIORITY_QUEUES[BLOCKED], newpcb, BLOCKED);
      printf("Changing state of %s to BLOCKED.\n", name);
    }
    else if( state == 2 ){
      PCB_BLOCK_ERR = PCB_insert(PRIORITY_QUEUES[BLOCKEDSUSPENDED], newpcb, BLOCKEDSUSPENDED);
      printf("Changing state of %s to BLOCKED-SUSPENDED.\n", name);
    }
    else {
      PCB_BLOCK_ERR = PCB_insert(PRIORITY_QUEUES[BLOCKEDSUSPENDED], newpcb, BLOCKEDSUSPENDED);
      printf("Changing state of %s to BLOCKED-SUSPENDED.\n", name);
    }
  }
  return PCB_BLOCK_ERR;
}

int punblock(char *name, PCBDLL **PRIORITY_QUEUES){
  PCB *temp;
  PCB *newpcb;
  int PCB_UNBLOCK_ERR = 0;
  int priority, pclass, state;
  // stack wtf
  // int memsize;
  // unsigned char *load;
  // unsigned char *exec;

  temp = PCB_find(name, PRIORITY_QUEUES);
  if( temp == NULL ){
    printf("Could not find the specified Process Control Block.\n");
    return PCB_UNBLOCK_ERR;
  }
  else {
    
    // Grab the temp values...
    priority = temp->priority;
    pclass = temp->pclass;
    state = temp->state;
    //memsize = temp->memsize;
    //load = temp->load;
    //exec = temp->exec;
    
    // Now remove the PCB
    PCB_remove(temp, PRIORITY_QUEUES);
    
    // Now make a new one
    newpcb = PCB_setup(name, priority, pclass, PRIORITY_QUEUES);

    // Stick it in the right place
    if( state == 0 ){
      PCB_UNBLOCK_ERR = PCB_insert(PRIORITY_QUEUES[READY], newpcb, READY);
      printf("Changing state of %s to READY.\n", name);
    }
    else if( state == 1 ){
      PCB_UNBLOCK_ERR = PCB_insert(PRIORITY_QUEUES[READY], newpcb, READY);
      printf("Changing state of %s to READY.\n", name);
    }
    else if( state == 2 ){
      PCB_UNBLOCK_ERR = PCB_insert(PRIORITY_QUEUES[READYSUSPENDED], newpcb, READYSUSPENDED);
      printf("Changing state of %s to READY-SUSPENDED.\n", name);
    }
    else {
      PCB_UNBLOCK_ERR = PCB_insert(PRIORITY_QUEUES[READYSUSPENDED], newpcb, READYSUSPENDED);
      printf("Changing state of %s to READY-SUSPENDED.\n", name);
    }
  }                                               
  return PCB_UNBLOCK_ERR;
}

int psuspend(char *name, PCBDLL **PRIORITY_QUEUES){
  PCB *temp;
  PCB *newpcb;
  int PCB_SUSPEND_ERR = 0;
  int priority, pclass, state;
  // stack wtf
  // int memsize;
  // unsigned char *load;
  // unsigned char *exec;

  temp = PCB_find(name, PRIORITY_QUEUES);
  if( temp == NULL ){
    printf("Could not find the specified Process Control Block.\n");
    return PCB_SUSPEND_ERR;
  }
  else {
    
    // Grab the temp values...
    priority = temp->priority;
    pclass = temp->pclass;
    state = temp->state;
    //memsize = temp->memsize;
    //load = temp->load;
    //exec = temp->exec;
    
    // Now remove the PCB
    PCB_remove(temp, PRIORITY_QUEUES);
    
    // Now make a new one
    newpcb = PCB_setup(name, priority, pclass, PRIORITY_QUEUES);

    // Stick it in the right place
    if( state == 0 ){
      PCB_SUSPEND_ERR = PCB_insert(PRIORITY_QUEUES[READYSUSPENDED], newpcb, READYSUSPENDED);
      printf("Changing state of %s to READY-SUSPENDED.\n", name);
    }
    else if( state == 1 ){
      PCB_SUSPEND_ERR = PCB_insert(PRIORITY_QUEUES[BLOCKEDSUSPENDED], newpcb, BLOCKEDSUSPENDED);
      printf("Changing state of %s to BLOCKED-SUSPENDED.\n", name);
    }
    else if( state == 2 ){
      PCB_SUSPEND_ERR = PCB_insert(PRIORITY_QUEUES[READYSUSPENDED], newpcb, READYSUSPENDED);
      printf("Changing state of %s to READY-SUSPENDED.\n", name);
    }
    else {
      PCB_SUSPEND_ERR = PCB_insert(PRIORITY_QUEUES[BLOCKEDSUSPENDED], newpcb, BLOCKEDSUSPENDED);
      printf("Changing state of %s to BLOCKED-SUSPENDED.\n", name);
    }
  }
  return PCB_SUSPEND_ERR;
}

int presume(char *name, PCBDLL **PRIORITY_QUEUES){
  PCB *temp;
  PCB *newpcb;
  int PCB_RESUME_ERR = 0;
  int priority, pclass, state;
  // stack wtf
  // int memsize;
  // unsigned char *load;
  // unsigned char *exec;

  temp = PCB_find(name, PRIORITY_QUEUES);
  if( temp == NULL ){
    printf("Could not find the specified Process Control Block.\n");
    return PCB_RESUME_ERR;
  }
  else {
    
    // Grab the temp values...
    priority = temp->priority;
    pclass = temp->pclass;
    state = temp->state;
    //memsize = temp->memsize;
    //load = temp->load;
    //exec = temp->exec;
    
    // Now remove the PCB
    PCB_remove(temp, PRIORITY_QUEUES);
    
    // Now make a new one
    newpcb = PCB_setup(name, priority, pclass, PRIORITY_QUEUES);

    // Stick it in the right place
    if( state == 0 ){
      PCB_RESUME_ERR = PCB_insert(PRIORITY_QUEUES[READY], newpcb, READY);
      printf("Changing state of %s to READY.\n", name);
    }
    else if( state == 1 ){
      PCB_RESUME_ERR = PCB_insert(PRIORITY_QUEUES[BLOCKED], newpcb, BLOCKED);
      printf("Changing state of %s to BLOCKED.\n", name);
    }
    else if( state == 2 ){
      PCB_RESUME_ERR = PCB_insert(PRIORITY_QUEUES[READY], newpcb, READY);
      printf("Changing state of %s to READY.\n", name);
    }
    else {
      PCB_RESUME_ERR = PCB_insert(PRIORITY_QUEUES[BLOCKED], newpcb, BLOCKED);
      printf("Changing state of %s to BLOCKED.\n", name);
    }
  }
  return PCB_RESUME_ERR;
}

int psetprio(char *argstr, PCBDLL **PRIORITY_QUEUES){
  PCB *temp;
  char *tokenPtr;
  char *name;
  int priority;
  int PCB_PRIORITY_ERR = 0;
  int temptemp;
  
  // Grab the args and place them in vars then drop to code below
  
  tokenPtr = strtok(argstr, " ");
  if (tokenPtr == NULL) {
    printf("No arguments supplied. Terminating.\n");
    return PCB_PRIORITY_ERR;
  }

  while (tokenPtr != NULL) {
    if (!strcmp(tokenPtr, "-n\0")){ // Name arg, pump again
      tokenPtr = strtok(NULL, " ");
      strcpy(name, tokenPtr);
    }
    else if (!strcmp(tokenPtr, "-p\0")){ // Prio arg, pump it
      tokenPtr = strtok(NULL, " ");
      priority = atoi(tokenPtr);
    }
    else {
      printf("Invalid supplied. Getting out of here.\n");
      return PCB_PRIORITY_ERR;
    }
    tokenPtr = strtok(NULL, " ");
  }

  if( !(priority >= -128 && priority <= 127) ){
    printf("Invalid priority.\n");
    return PCB_PRIORITY_ERR;
  }
  else if( strlen(name) > 8 ){
    printf("Invalid Process Control Block identifier.\n");
    return PCB_PRIORITY_ERR;
  }
  else {
    temp = PCB_find(name, PRIORITY_QUEUES);
    if( temp == NULL ){
      printf("Could not find the specified Process Control Block.\n");
      return PCB_PRIORITY_ERR;
    }
    else {
      printf("Successfully changed the priority of PCB: %s to %d\n", name, priority);
      temp->priority = priority;
      temptemp = temp->state;
      PCB_PRIORITY_ERR = PCB_remove(temp, PRIORITY_QUEUES);
      PCB_PRIORITY_ERR = PCB_insert(PRIORITY_QUEUES[temptemp], temp, temptemp);
    }  
  }
  return PCB_PRIORITY_ERR;
}
