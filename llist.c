#include <stdlib.h>
#include "llist.h"
#include <stdio.h>

llist init_snake(int l_size, int c_size)
{
  int i;
  element *snake = malloc(sizeof(element));
  snake->val = 1;
  snake->next = NULL;
  snake->x = c_size/2;
  snake->y= l_size/2;

  
  for(i = 0; i < 3; i++){
    snake = add_to_head(snake, 2, snake->x - 1, snake->y);
   }

  return snake;
}

llist add_to_head(llist list, int val, int x, int y)
{
  element *new = malloc(sizeof(element));
  new->val = val;
  new->next = list;
  new->x = x;
  new->y = y;
  return new;
}


 llist add_to_tail(llist list, int val, int x, int y)
{
  element* tmp;
  element *new = malloc(sizeof(element));
  new->val = val;
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
