#ifndef QUEUE_H
#define QUEUE_H

#include "status.h"

typedef void* QUEUE;

QUEUE queue_init_default(void);
void queue_destroy(QUEUE*);
Boolean queue_is_empty(QUEUE);
Status queue_insert(QUEUE, int);
int queue_front(QUEUE, Status*);
Status queue_service(QUEUE);


#endif