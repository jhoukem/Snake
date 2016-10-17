#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include "input.h"

#define X 0
#define Y 1
#define UP 'z'
#define LEFT 'q'
#define RIGHT 'd'
#define DOWN 's'


void init_input_arg(input_arg ** arg)
{
  *arg = (input_arg*) malloc(sizeof(input_arg));
  (*arg)->x = 1;
  (*arg)->y = 0;
  (*arg)->stop = 0;
  sem_init(&(*arg)->sem, 0, 1);
}

void changemode(int dir)
{
  static struct termios oldt, newt;
  
  if (dir == 1)
    {
      tcgetattr( STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~( ICANON | ECHO );
      tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    }else{
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  }
}

int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;
  
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  
  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);
  
  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);
  
}



void * handle_input(void * arg){
  
  input_arg * input_arg = (struct input_arg *) arg;

  changemode(1);

  while(!input_arg->stop){
    
    if(kbhit()){
      // allow only one input per update.
      if(sem_trywait(&input_arg->sem) == 0){
	switch(getchar()){
	case UP:
	  if(input_arg->y != 1){
	    input_arg->x = 0; input_arg->y = -1;
	  }
	  break;
	case LEFT:
	  if(input_arg->x != 1){
	    input_arg->x = -1; input_arg->y = 0;
	  }
	  break;
	case DOWN:
	  if(input_arg->y != -1){
	    input_arg->x = 0; input_arg->y = 1;
	  }
	  break;
	case RIGHT:
	  if(input_arg->x != -1){
	    input_arg->x = 1; input_arg->y = 0;
	  }
	  break;
	default: break;
	}
      }
    }
  }
  changemode(0);
  pthread_exit(NULL);
}
