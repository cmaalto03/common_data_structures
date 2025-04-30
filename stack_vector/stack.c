#include "stack.h"
#include <stdlib.h>
#include <stdio.h>


// using a vector!

// add each to stack, check if match, then pop off match, then check if stack is empty
struct stack
{
    int* data;
    int size;
    int capacity;
};

typedef struct stack Stack;


STACK stack_init_default(void)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    if (stack != NULL)
    {
        stack->size = 0;
        stack->capacity = 1;
        stack->data = (int*)malloc(sizeof(int) * stack->capacity);

        if (stack->data == NULL)
        {
            free(stack);
            return NULL;
        }        
    }
    return stack;
}

void stack_destroy(STACK* phStack)
{
    Stack* pStack = (Stack*)*phStack;

    free(pStack->data);
    free(pStack);

    phStack = NULL;
}

Status stack_push(STACK hStack, int value)
{
    Stack* pStack = (Stack*)hStack;

    if(pStack->size == pStack->capacity)
    {
        int* new = (int*)malloc(sizeof(int)*pStack->capacity * 2);

        if (new == NULL)
        {
            return FAILURE;
        }

        for(int i = 0; i < pStack->size; i++)
        {
            new[i] = pStack->data[i];
        }

        free(pStack->data);
        pStack->data = new;

        pStack->capacity*=2;
    }
    pStack->data[pStack->size++] = value;

    return SUCCESS;
}

Boolean stack_is_empty(STACK hStack)
{
    Stack* pStack = (Stack*)hStack;

    return (pStack->size == 0) ? TRUE: FALSE;
}

Status stack_pop(STACK hStack)
{
    Stack* pStack = (Stack*)hStack;

    if (stack_is_empty(hStack) == TRUE)
    {
        return FAILURE;
    }

    pStack->size--;
    return SUCCESS;

}
int stack_top(STACK hStack, Status* pStatus)
{
    Stack* pStack = (Stack*)hStack;

    if (stack_is_empty(hStack))
    {
        if (pStatus != NULL)
            return *pStatus = FAILURE;
        
            return -1;
    }

    if (pStatus != NULL)
    {
        *pStatus = SUCCESS;
    }
   
    return pStack->data[pStack->size-1];
}