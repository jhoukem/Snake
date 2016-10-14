#include <stdlib.h>
#include "llist.h"
#include <stdio.h>

#define SOL 0
#define HEAD 1
#define BODY 2
#define APPLE 3

llist init_snake(int l_size, int c_size)
{
  int i;
  element *snake = malloc(sizeof(element));
  snake->val = HEAD;
  snake->next = NULL;
  snake->x = c_size/2;
  snake->y= l_size/2;

  
  for(i = 1; i <= 3; i++){
    add_to_tail(snake, snake->x - i, snake->y);
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

llist add_to_head(llist list, int x, int y)
{
  element *new = malloc(sizeof(element));
  new->val = HEAD;
  new->next = list;
  new->x = x;
  new->y = y;
  new->next->val = BODY;
  return new;
}

llist move_last_to_head(llist snake, int x, int y, int ** grid)
{

  element * elem = snake;
  element * new_head;
  
  while(elem->next->next != NULL){
    elem = elem->next;
  }
  // ??? elem->next;
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

 llist add_to_tail(llist list, int x, int y)
{
  element* tmp;
  element *new = malloc(sizeof(element));
  new->val = BODY;
  new->x = x;
  new->y = y;
  new->next = NULL;

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
