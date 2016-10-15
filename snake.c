#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include "grid.h"
#include "llist.h"

#define SIZE 16

int stop = 0;


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  
  if(ch != EOF){
    ungetc(ch, stdin);
    return 1;
  }
  
  return 0;
}



void* handle_input(void * arg){
  
  int * input = (int *) arg;
  
  while(!stop){
    
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
    pthread_exit(NULL);
}

int main(){

  int input[2] = {0,-1};
  
  pthread_t input_handling;
  int ** grid;
  llist snake;
  
  grid = init_grid(SIZE, SIZE);
  snake = init_snake(SIZE, SIZE, grid);

  
  if(pthread_create(&input_handling, NULL, handle_input, (void *) input)){
    perror("pthread_create");
    exit(1);
  }
  
  while(1){  

    if(update_grid(grid, SIZE, SIZE, &snake, input) < 0)
      break;
    display_grid(grid, SIZE, SIZE);
    usleep(500 * 300);
  }

  stop = 1;
  
  if(pthread_join(input_handling, NULL)){
    perror("pthread_join");
    exit(1);
  }
  
  return 0;
}
