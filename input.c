#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

#define X 0
#define Y 1
#define UP 'z'
#define LEFT 'q'
#define RIGHT 'd'
#define DOWN 's'


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
  
  int * input = (int *) arg;
  changemode(1);

  while(!input[2]){
    
    if(kbhit()){
      switch(getchar()){
      case UP:
	if(input[Y] != 1){
	  input[X] = 0; input[Y] = -1;
	}
	break;
      case LEFT:
	if(input[X]!= 1){
	  input[X] = -1; input[Y] = 0;
	}
	break;
      case DOWN:
	if(input[Y] != -1){
	  input[X] = 0; input[Y] = 1;
	}
	break;
      case RIGHT:
	if(input[X] != -1){
	  input[X] = 1; input[Y] = 0;
	}
	break;
      default: break;
      }
    }
  }
  changemode(0);
  pthread_exit(NULL);
}
