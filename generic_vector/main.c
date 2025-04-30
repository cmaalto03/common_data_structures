/**********************************************************************
Program: <generic_vector>
Author: <Connor Aalto>
Date: <4/30/25>
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"

ITEM makeItem(ITEM);
void freeItem(ITEM*);
int main(int argc, char* argv[])
{
    GENERIC_VECTOR hVector = generic_vector_init_default(makeItem, freeItem);

    // push values 0 - 99
    for (int i = 0; i < 100; i++)
    {
        generic_vector_push_back(hVector, &i);
    }

    printf("Capacity is %d\n", generic_vector_get_capacity(hVector));
    printf("Size is %d\n", generic_vector_get_size(hVector));

    ITEM* pArrayAddress = generic_vector_at(hVector, 0);
    int* pHeapAddress = (int*)*pArrayAddress;

    printf("Element at index 0 is %d\n", *pHeapAddress);

    for (int i = 0; i < 100; i++)
    {
        generic_vector_pop_back(hVector);
    }

    printf("generic_vector is empty is %s\n", generic_vector_is_empty(hVector) ? "TRUE" : "FALSE");

    generic_vector_destroy(&hVector);
    
}

ITEM makeItem(ITEM value) {
    int* pInt = (int*)malloc(sizeof(int));
    if (pInt != NULL) {
        *pInt = *(int*)value;

    }
    return pInt;
}

void freeItem(ITEM* phItem) {
    int* pItem = (int*)*phItem;
    free(pItem);
    *phItem = NULL;
}