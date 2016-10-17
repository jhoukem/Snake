#ifndef INPUT
#define INPUT

#include <semaphore.h>
#include <stdlib.h>

typedef struct input_arg input_arg;
struct input_arg
{
  int x, y, stop;
  sem_t sem;
};

int kbhit(void);
void init_input_arg(input_arg ** arg);
void * handle_input(void * arg);
void changemode(int dir);
#endif
