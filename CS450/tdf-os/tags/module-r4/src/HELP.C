#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpx_supt.h"

int help(char *argstr)
{
  int HELP_ERR = 0;
  char *tokenPtr;

  tokenPtr = strtok(argstr," ");
  
  if(tokenPtr == NULL){
    printf("help describes how to use a specific tdf-os function\n\n");
    printf("              Usage of help:\n\n");
    printf("\tEx. help date\t\thow to use the function 'date'\n");
    printf("Tdf-os function list:\n");
    printf("\tdate\n\tdispatch\n\tdisplay\n\texit\n\thistory\n\tload\n\tloadr3\n\tversion\n\tpcreate\n\tpdelete\n\tpblock\n\tpunblock\n\tpsuspend\n\tpresume\n\tpsetprio\n\tpshow\n\tpshowall\n\tpshowblk\n\tpshowrd\n\n");
    return HELP_ERR;
  }

  while (tokenPtr != NULL){
    if(!strcmp(tokenPtr, "date\0")){
      printf("return or set the system date\n");
      printf("\tUsage of date:\n");
      printf("\tdate\t\treturn the system date\n");
      printf("\tdate -s yyyymmdd\t\tchange the system date\n");
      break;
    }
    else if(!strcmp(tokenPtr, "dispatch\0")){
      printf("executes the processes in the READY queue\n");
      printf("\tUsage: dispatch\n");
      break;
    }
    else if (!strcmp(tokenPtr, "display\0")){
      printf("display all .MPX files in the current directory\n");
      printf("\tdisplay optionally accepts an absolute or relative \n");
      printf("\tdirectory path as an option\n");
      break;
    }
    else if(!strcmp(tokenPtr, "exit\0")){
      printf("exit will quit the tdf-os session\n");
      printf("\texit accepts no arguments\n");
      printf("\texit will prompt for confirmation\n");
      break;
    }
    else if(!strcmp(tokenPtr, "help\0")) {
      printf("help helps you help yourself\n");
      printf("help accepts an optional argument [command] where \n");
      printf("[command] is another commands name\n");
      break;
    }
    else if(!strcmp(tokenPtr, "history\0")){
      printf("history displays all commands previously entered into the tdf-os\n");
      printf("\thistory accepts no arguments\n");
      break;
    }
    else if(!strcmp(tokenPtr, "load\0")){
      printf("loads a specified MPX process into the SUSPENDED queue\n");
      printf("\tUsage: load -n [name] -p [priority]\n");
      printf("\treturns an error if supplied inproper arguments\n");
      break;
    }
    else if(!strcmp(tokenPtr, "loadr3\0")){
      printf("loads the processes for MPX Module R3\n");
      printf("\tUsage: loadr3\n");
      break;
    }
    else if(!strcmp(tokenPtr, "pcreate\0")){
      printf("creates a new PCB and puts it in the ready queue\n");
      printf("\tUsage: pcreate [pcbname]\n");
      printf("\tOnce called pcreate requires user input of priority, state, and class\n");
      break;
    }
    else if(!strcmp(tokenPtr, "pblock\0")){
      printf("places the specified PCB in the blocked state removing it from ready queue\n");
      printf("\tUsage: pblock [pcbname]\n");
      break;
    }
    else if(!strcmp(tokenPtr, "pdelete\0")){
      printf("removes a PCB and frees its memory\n");
      printf("\tUsage: pdelete [pcbname]\n");
      printf("\treturns an error if PCB does not exist\n"); 
      break;
    }
    else if(!strcmp(tokenPtr, "presume\0")){
      printf("returns a process from the suspended state\n");
      printf("\tUsage: presume [pcbname]\n");
      break;
    }
    else if(!strcmp(tokenPtr, "psetprio\0")){
      printf("sets the priority of a specified PCB\n");
      printf("\tpriority must be in range -128 to 127\n");
      printf("\tUsage: psetprio -n [pcbname] -p [priority]\n");
      break;
    }
    else if(!strcmp(tokenPtr, "pshow\0")){
      printf("display pertinent information for specified PCB\n");
      printf("\tUsage: pshow [pcbname]\n");
      break;
    }
    else if(!strcmp(tokenPtr, "pshowall\0")){
      printf("display information on every PCB regardless of status\n");
      printf("\tpshowall takes no arguments\n");
      break;
    }
    else if(!strcmp(tokenPtr, "pshowblk\0")){
      printf("display information on every PCB with status 'blocked'\n");
      printf("\tpshowblk takes no arguments\n");
      break;
    }
    else if(!strcmp(tokenPtr, "pshowrd\0")){
      printf("display information on every PCB with status 'ready'\n");
      printf("\tpshowrd takes no arguments\n");
      break;
    }
    else if(!strcmp(tokenPtr, "psuspend\0")){
      printf("places the specified PCB in the suspended state\n");
      printf("Usage: psuspend [pcbname]\n");
      break;
    }
    else if(!strcmp(tokenPtr, "punblock\0")){
      printf("unblocks the specified PCB returning it to the ready queue\n");
      printf("\tUsage: punblock [pcbname]\n");
      break;
    }
    else if(!strcmp(tokenPtr, "version\0")){
      printf("version displays the current version of tdf-os\n");
      printf("\tversion accepts no arguments\n");
      break;
    }
    else {
      printf("No help to be found.  Move along.\n");
      break;
    }
    tokenPtr = strtok(NULL, " ");
  }
  
  return HELP_ERR;
}
