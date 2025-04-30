#include <stdlib.h>
#include "priority_queue.h"

const int GROW_FACTOR = 2;

struct item
{
    int data;
    int priority_level;
};

typedef struct item Item;

struct priority_queue {
    int capacity;
    int size;
    int index_front;
    Item** data;
};

typedef struct priority_queue Priority_queue;

Item* makeItem(int, int);
void freeItem(Item**);

PRIORITY_QUEUE priority_queue_init_default(void)
{
    Priority_queue* pQueue = (Priority_queue*)malloc(sizeof(Priority_queue));

    if (pQueue != NULL)
    {
        pQueue->size = 0;
        pQueue->capacity = 1;
        pQueue->index_front = 0;
        pQueue->data = (Item**)malloc(sizeof(Item*)*pQueue->capacity);

        if (pQueue->data == NULL)
        {
            free(pQueue);
            return NULL;
        }
    }
    return pQueue;
}

void fix_up(Priority_queue* pQueue, int index)
{
    
    int pIndex = (index-1)/2;

    if (pIndex >= pQueue->index_front)
    {
        if (pQueue->data[index]->priority_level > pQueue->data[pIndex]->priority_level)
        {
            int temp1 = pQueue->data[index]->data;
            int temp2 = pQueue->data[index]->priority_level;


            pQueue->data[index]->data = pQueue->data[pIndex]->data;
            pQueue->data[index]->priority_level = pQueue->data[pIndex]->priority_level;


            pQueue->data[pIndex]->data = temp1;
            pQueue->data[pIndex]->priority_level = temp2;

            fix_up(pQueue, pIndex);
        }
  
    }
}

void fix_down(Priority_queue* pQueue, int index)
{

    int left_index = index * 2 + 1;
    int right_index = index * 2 + 2;
    int greatest_index;

    if (left_index < (pQueue->size + pQueue->index_front))
    {

        if (right_index < pQueue->size + pQueue->index_front)
        {
            greatest_index = (pQueue->data[left_index]->priority_level > pQueue->data[right_index]->priority_level) ? left_index : right_index;

        }
        else
        {
            greatest_index = left_index;
        }
        if (pQueue->data[index]->priority_level < pQueue->data[greatest_index]->priority_level)
        {
            int temp1 = pQueue->data[index]->data;
            int temp2 = pQueue->data[index]->priority_level;

            pQueue->data[index]->data = pQueue->data[greatest_index]->data;
            pQueue->data[index]->priority_level = pQueue->data[greatest_index]->priority_level;

            pQueue->data[greatest_index]->data = temp1;
            pQueue->data[greatest_index]->priority_level = temp2;
            fix_down(pQueue, greatest_index);
        }
    }

}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
    Priority_queue* pQueue = (Priority_queue*)hQueue;

    if (pQueue->size >= pQueue->capacity)
    {
         Item** new_data = (Item**)malloc(sizeof(Item*) * pQueue->capacity * GROW_FACTOR);

        if (new_data == NULL)
        {
            return FAILURE;
        }

        for(int i = 0; i < pQueue-> size; i++)
        {
            new_data[i] = pQueue->data[i];
        }

        free(pQueue->data);
        pQueue->data = new_data;
        pQueue->capacity *= GROW_FACTOR;
        pQueue->index_front = 0;
    }
    Item* new = makeItem(data_item, priority_level);
    pQueue->data[pQueue->index_front + pQueue->size % pQueue->capacity] = new;

    fix_up(pQueue, pQueue->index_front + pQueue->size);
    pQueue->size++;

    return SUCCESS;
}


Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
    Priority_queue* pQueue = (Priority_queue*)hQueue;

    if (priority_queue_is_empty(pQueue))
    {
        return FAILURE;
    }

    pQueue->data[pQueue->index_front]->data = pQueue->data[pQueue->index_front + pQueue->size -1]->data;
    pQueue->data[pQueue->index_front]->priority_level = pQueue->data[pQueue->index_front + pQueue->size -1]->priority_level;

    freeItem(&pQueue->data[pQueue->index_front + pQueue->size - 1]);

    pQueue->size--;
    fix_down(pQueue, pQueue->index_front);

    return SUCCESS;
}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus)
{
    Priority_queue* pQueue = (Priority_queue*)hQueue;


    if(priority_queue_is_empty(hQueue) == TRUE)
    {
        if (pStatus != NULL)
        {
            *pStatus = FAILURE;
        }
        return 0xBEEF;
    }

    if (pStatus != NULL)
    {
        *pStatus = SUCCESS;
    }
    
    Item* pItem = (Item*)pQueue->data[pQueue->index_front];

    return pItem->data;
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
    Priority_queue* pQueue = (Priority_queue*)hQueue;

    return (pQueue->size <=0) ? TRUE : FALSE; 

}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
    Priority_queue* pQueue = (Priority_queue*)*phQueue;  

    for(int i = pQueue->index_front; i < pQueue->index_front + pQueue->size; i++)
    {
        freeItem(&pQueue->data[i]);
    }
    free(pQueue->data);
    free(pQueue);

    *phQueue = NULL;
}

Item* makeItem(int value, int priority) {
    Item* pItem = (Item*)malloc(sizeof(Item));
    if (pItem != NULL) {
        pItem->data = value;
        pItem->priority_level = priority;
    }
    return pItem;
}

void freeItem(Item** phItem) {
    free(*phItem);
    phItem = NULL;
}
