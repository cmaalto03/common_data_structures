#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

struct node;
typedef struct node Node;

struct node
{
    int data;
    Node* next;
};

struct stack
{
    Node* head;
};

typedef struct stack Stack;

STACK stack_init_default(void)
{
    Stack* stack = malloc(sizeof(Stack));

    if (stack != NULL)
    {
        return stack;
    }
}

void stack_destroy(STACK* phStack)
{
    Stack* pStack = (Stack*)*phStack;

    Node* delete_me;

    while (pStack->head != NULL)
    {
        delete_me = pStack->head;
        pStack->head = pStack->head->next;
        free(delete_me);
    }
    free(pStack);

    phStack = NULL;

}

Status stack_push(STACK hStack, int value)
{
    Stack* pStack = (Stack*)hStack;

    Node* new = malloc(sizeof(Node));

    if (new == NULL)
    {
        return FAILURE;

    }

    new->data = value;
    new->next = pStack->head;

    pStack->head = new;
}

Boolean stack_is_empty(STACK hStack)
{
   Stack* pStack = (Stack*)hStack;

   return pStack->head == NULL;
}

Status stack_pop(STACK hStack)
{
    Stack* pStack = (Stack*)hStack;

    pStack->head = pStack->head->next;

    return SUCCESS;

}
int stack_top(STACK hStack, Status* pStatus)
{
    Stack* pStack = (Stack*)hStack;

    if(stack_is_empty(hStack))
    {
        exit(1);
    }
    return pStack->head->data;
}