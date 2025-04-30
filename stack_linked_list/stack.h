#ifndef STACK_H
#define STACK_H

#include "status.h"

typedef void* STACK;

STACK stack_init_default(void);
void stack_destroy(STACK*);


Boolean stack_is_empty(STACK);
Status stack_push(STACK, int);
Status stack_pop(STACK);
int stack_top(STACK, Status*);


#endif