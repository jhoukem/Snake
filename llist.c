#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

#define SOL 0
#define HEAD 1
#define BODY 2
#define APPLE 3
#define SNAKE_SIZE_BEGIN 3

int get_llist_size(llist list)
{
  int counter = 0;

  while(list != NULL){
    counter++;
    list = list->next;
  }
  return counter;
}
void free_llist(llist snake)
{
  
  element * elem;

  while(snake != NULL){
    elem = snake->next;
    free(snake);
    snake = elem;
  }
}


llist init_snake(int l_size, int c_size, int ** grid)
{
  int i;
  element *snake = malloc(sizeof(element));
  snake->val = HEAD;
  snake->next = NULL;
  snake->x = c_size/2;
  snake->y= l_size/2;
  grid[snake->y][snake->x] = snake->val;
  
  for(i = 1; i <= SNAKE_SIZE_BEGIN; i++){
    add_to_tail(snake, snake->x - i, snake->y, grid);
   }
    
  return snake;
}

void display(llist list){

  do{
    printf("%d", list->val);
    list = list->next;
  }
  while(list != NULL);
  printf("\n");
  
}

llist add_to_head(llist snake, int x, int y, int ** grid)
{

  element *new = malloc(sizeof(element));
  new->val = HEAD;
  new->next = snake;
  new->x = x;
  new->y = y;
  new->next->val = BODY;

  grid[new->y][new->x] = new->val;
  grid[snake->y][snake->x] = snake->val;
  
  
  return new;
}

llist move_last_to_head(llist snake, int x, int y, int ** grid)
{

  element * elem = snake;
  element * new_head;
  
  while(elem->next->next != NULL){
    elem = elem->next;
  }
  
  // Save the last element.
  new_head = elem->next;
  // Remove the last element from the list and the grid
  elem->next = NULL;
  grid[new_head->y][new_head->x] = SOL;

  // Put the last element to the top of the list
  new_head->x = x;
  new_head->y = y;
  new_head->val = HEAD;
  grid[new_head->y][new_head->x]= HEAD;

  // Transform the last head in body
  new_head->next = snake;
  new_head->next->val = BODY;
  grid[new_head->next->y][new_head->next->x]= new_head->next->val;
  
  return new_head;
}

 llist add_to_tail(llist list, int x, int y, int ** grid)
{
   
  element* tmp;
  element *new = malloc(sizeof(element));
  new->val = BODY;
  new->x = x;
  new->y = y;
  new->next = NULL;
  grid[new->y][new->x] = new->val;

  
  if(list == NULL){
    return new;
  } 

  tmp = list;
  while(tmp->next != NULL){
    tmp = tmp->next;
  }
  tmp->next = new;

  return list;
}
