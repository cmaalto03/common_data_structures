/**********************************************************************
Program: <Stack (using linked list)>
Author: <Connor Aalto>
Date: <1/30/25>
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int main(int argc, char* argv[])
{
    STACK stack = stack_init_default();

    if (stack == NULL)
    {
        printf("c'tor failed\n");
        exit(1);
    }

    printf("is empty is %d\n", stack_is_empty(stack) == TRUE);
    stack_push(stack, 5);
    stack_push(stack, 7);

    printf("is empty is %d\n", stack_is_empty(stack) == TRUE);
    printf("Top is %d\n", stack_top(stack, NULL));

    stack_pop(stack);
    printf("is empty is %d\n", stack_is_empty(stack) == TRUE);

    printf("Top is %d\n", stack_top(stack, NULL));

    stack_destroy(&stack);
    return 0;
}