/**********************************************************************
Program: <Queue using circular buffer>
Author: <Connor Aalto>
DateL <1/30/2025>
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char* argv[])
{
    QUEUE q = queue_init_default();

    if (q == NULL)
    {
        printf("Malloc failed\n");
        exit(1);
    }

    queue_insert(q, 5);
    queue_insert(q, 10);

    printf("Front is %d\n", queue_front(q, NULL));

    queue_service(q);
    printf("Front is %d\n", queue_front(q, NULL));


    printf("Queue is empty is %d\n", queue_is_empty(q));
    queue_service(q);
    printf("Queue is empty is %d\n", queue_is_empty(q));

    queue_destroy(&q);
    return 0;
}