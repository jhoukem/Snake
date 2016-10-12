#include <stdlib.h>
#include "llist.h"

llist add_to_head(llist list, int val)
{
  element *new = malloc(sizeof(element));
  new->val = val;
  new->next = list;
  return new;
}

llist add_to_tail(llist list, int val)
{
  element* tmp;
  element *new = malloc(sizeof(element));
  new->val = val;
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
