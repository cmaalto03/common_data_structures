/**********************************************************************
Program: <Priority queue implemented as max-heap>
Author: <Connor Aalto>
Date: <4/4/25>
***********************************************************************/

#include <stdio.h>
#include "priority_queue.h"

int main(int argc, char* argv[])
{
    PRIORITY_QUEUE pq = priority_queue_init_default();

    // for simplicity, treating priority_level the same as data_item in insert
    for (int i = 0; i < 300; i++)
    {
        priority_queue_insert(pq, i, i);

    }

    printf("%d\n", priority_queue_front(pq, NULL)); // expected: 299

    priority_queue_service(pq);
    printf("%d\n", priority_queue_front(pq, NULL)); // expected: 298

    priority_queue_insert(pq, 300, 300);      
    priority_queue_insert(pq, 0, 0);  
    priority_queue_insert(pq, 200, 200);            
        
      

    printf("%d\n", priority_queue_front(pq, NULL)); // expected: 300
    priority_queue_service(pq);
    printf("%d\n", priority_queue_front(pq, NULL)); // expected: 298


    while (priority_queue_is_empty(pq) == FALSE)
    {
        priority_queue_service(pq);
    }

    printf("Priority queue is empty: %d\n", priority_queue_is_empty(pq)); // expected: 1 (For TRUE)
    priority_queue_destroy(&pq);

    return 0;

}