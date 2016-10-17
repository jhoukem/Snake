#ifndef H_GRID
#define H_GRID

#include "llist.h"
#include "input.h"

void free_grid(int ** grid, int l_size);
int get_real_int(int x, int size);
int ** init_grid(int l_size, int c_size);
int update_grid(int ** grid, int l_size, int c_size, llist *snake, input_arg * input);
void display_grid(int ** grid, int l_size, int c_size);


#endif
