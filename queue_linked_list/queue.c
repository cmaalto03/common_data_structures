#include "queue.h"
#include <stdlib.h>
#include <stdio.h>


struct node;
typedef struct node Node;

struct node
{
    int data;
    Node* next;
};

struct queue
{
    Node* head;
    Node* tail;
};

typedef struct queue Queue;

QUEUE queue_init_default(void)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));

    if (q != NULL)
    {
        q->head = NULL;
        q->tail = NULL;
    }

    return q;
}        


void queue_destroy(QUEUE* phQueue)
{
    Queue* q = (Queue*)*phQueue;

    Node* delete_me;
    while (q->head != NULL)
    {
        delete_me = q->head;
        q->head = q->head->next;

        free(delete_me);
    }

    free(q);

    *phQueue = NULL;
}

Boolean queue_is_empty(QUEUE hQueue)
{
   Queue* q = (Queue*)hQueue;

   return (q->tail == NULL && q->head == NULL) ? TRUE : FALSE;
}

int queue_front(QUEUE hQueue, Status* s)
{
    Queue* q = (Queue*)hQueue;

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
    
    return q->head->data;
}

Status queue_insert(QUEUE hQueue, int data)
{
    Queue* q = (Queue*)hQueue;

    Node* new = (Node*)malloc(sizeof(Node));

    if (new == NULL)
    {
        return FAILURE;
    }

    new->data = data;
    new->next = NULL;

    if (q->tail== NULL)
    {
        q->head = new;
        q->tail = new;
    }
    else
    {
        q->tail->next = new;
        q->tail = new;
    }
    return SUCCESS;
}

Status queue_service(QUEUE hQueue)
{
    Queue* q = (Queue*)hQueue;

    if (queue_is_empty(hQueue))
    {
        return FAILURE;
    }

    Node* delete_me = NULL;
    delete_me = q->head;

    q->head = q->head->next;
    free(delete_me);

    if (q->head == NULL)
    {
        q->tail = NULL;
    }
    
    return SUCCESS;
}
