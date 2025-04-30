/**********************************************************************
Program: <Queue implimented as linked list -- Ferry Loading>
Author: <Connor Aalto>
Date: <3/20/24>
Purpose: The purpose of this program is to solve the ferry loading problem
from UVa online judege.

It also serves as driver code for my queue implementation

https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=39&page=show_problem&problem=1202#google_vignette


It achieves this by using two queues (one for the right, one for the left),
and enqueues each side until it is full. It then iterates through and services
each queue until the trip for that ferry is full, and switches to the other side 
(with a variable to track the side).
It does this until both queues are empty.

***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

enum direction {LEFT, RIGHT};
typedef enum direction Direction;

Boolean ferry_load(void);
void clear_keyboard_buffer(void);
int main(int argc, char* argv[])
{
    int numCases;
    int i;

    fscanf(stdin, "%d", &numCases);

    for (i = 0; i < numCases; i++)
    {
        printf("%d\n", ferry_load());
    }
    return 0;
}

Boolean ferry_load()
{
    int ferry_length;
    int num_of_cars;

    int i = 0;
    int car_length;


    QUEUE q_left = queue_init_default();
    QUEUE q_right = queue_init_default();


    fscanf(stdin, "%d %d", &ferry_length, &num_of_cars);



    while (i < num_of_cars)
    {
        char* char_buff = malloc(sizeof(char) * 10);

        fscanf(stdin, "%d %s", &car_length, char_buff);

        if (char_buff[0] == 'r')
        {
            queue_insert(q_right, car_length);
        }
        
        if (char_buff[0] == 'l')
        {
            queue_insert(q_left, car_length);
        }
        free(char_buff);

        i++;
    }

    Direction current_ferry_pos = LEFT;
    int cm_sum = 0;

    int num_ferry_trips = 0;

    while (!queue_is_empty(q_left) || !queue_is_empty(q_right))
    {
        if (current_ferry_pos == LEFT)
        {
            cm_sum = 0; 

            while (queue_is_empty(q_left) != TRUE && cm_sum + queue_front(q_left, NULL) <= ferry_length * 100)
            {
                cm_sum += queue_front(q_left, NULL);
                queue_service(q_left);
            }

            current_ferry_pos = RIGHT;
            num_ferry_trips++;
        }
        else 
        {
            cm_sum = 0;  

            while (queue_is_empty(q_right) != TRUE && cm_sum + queue_front(q_right, NULL) <= ferry_length * 100)
            {
                cm_sum += queue_front(q_right, NULL);
                queue_service(q_right);
            }

            current_ferry_pos = LEFT;
            num_ferry_trips++;
        }
    }

    queue_destroy(&q_left);
    queue_destroy(&q_right);
    
    return num_ferry_trips;
}

void clear_keyboard_buffer(void)
{
    char c = 'a';

    while (c != '\n')
    {
        scanf("%c", &c);
    }
}
