#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>

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
      case 'z':
	if(input[1] != 1){
	  input[0] = 0; input[1] = -1;
	}
	break;
      case 'q':
	if(input[0]!= 1){
	  input[0] = -1; input[1] = 0;
	}
	break;
      case 's':
	if(input[1] != -1){
	  input[0] = 0; input[1] = 1;
	}
	break;
      case 'd':
	if(input[0] != -1){
	  input[0] = 1; input[1] = 0;
	}
	break;
      default: break;
      }
    }
  }
  changemode(0);
  pthread_exit(NULL);
}
