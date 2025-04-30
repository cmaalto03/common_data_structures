#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

struct circBuff 
{
    int size;
    int capacity;
    int indexFront;
    int* data;
};

typedef struct circBuff CircBuff;

QUEUE queue_init_default(void)
{
   CircBuff* new = malloc(sizeof(CircBuff));

   if (new != NULL)
   {
        new->size = 0;
        new->capacity = 1;
        new->indexFront = 0;
        new->data = (int*)malloc(sizeof(int) * new->capacity);

        if (new->data == NULL)
        {
            free(new);
            return NULL;
        }
   }
   return (QUEUE)new;
}        


void queue_destroy(QUEUE* phQueue)
{
    CircBuff* pq = (CircBuff*)*phQueue;

    free(pq->data);
    free(pq);

    phQueue = NULL;
}

Boolean queue_is_empty(QUEUE hQueue)
{
    CircBuff* pq = (CircBuff*)hQueue;

    return (pq->size == 0) ? TRUE: FALSE;
}

int queue_front(QUEUE hQueue, Status* s)
{
    CircBuff* pq = (CircBuff*)hQueue;

    if(queue_is_empty(hQueue) == TRUE)
    {
        if (s != NULL)
        {
            *s = FAILURE;
        }
        return 0xBEEF;
    }

    if (s != NULL)
    {
        *s = SUCCESS;
    }
    
    return pq->data[pq->indexFront];
}

Status queue_insert(QUEUE hQueue, int value)
{
    CircBuff* pq = (CircBuff*)hQueue;

    if (pq->size >= pq->capacity)
    {
        int* new = (int*)malloc(sizeof(int) * pq->capacity*2);

        if (new == NULL)
        {
            return FAILURE;
        }
    
        for (int i = 0; i < pq->size; i++)
        {
            new[i] = pq->data[(pq->indexFront + i) % pq->capacity];
        }

        free(pq->data);
        pq->data= new;
        pq->capacity*=2;
        pq->indexFront = 0;
    }

    pq->data[(pq->indexFront + pq->size) % pq->capacity] = value;
    pq->size++;
    return SUCCESS;
}

Status queue_service(QUEUE hQueue)
{
    CircBuff* pq = (CircBuff*)hQueue;


    if (queue_is_empty(hQueue))
    {
        return FAILURE;
    }

    // make sure to handle cases where it rolls over
    pq->indexFront = (pq->indexFront + 1) % pq->capacity;
    pq->size--;

    return SUCCESS;
}


