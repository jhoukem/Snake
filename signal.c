#include <signal.h>
#include <stdio.h>
#include "input.h"

void handler(int sig)
{
  if(sig == SIGCONT){
    changemode(1);
  }
}

void set_handler()
{
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  if (sigaction(SIGCONT, &action, NULL) != 0){
    fprintf(stderr, "Erreur sigaction\n");
    exit(1);
  } 
}

