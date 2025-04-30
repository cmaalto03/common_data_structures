/**********************************************************************
Program: <avl_Tree>
Author: <Connor Aalto>
Date: <4/15/25>
Purpose: The purpose of this program is to implement an avl tree (see header file
for all functions). Correctly impliments insertion and deletion, and rebalances
with rotations

In the driver program, chose to insert the key and data as the same value
for simplicity. Driver tests insertion, deletion, and LL, RR, LR, and RL rotations throughout.
***********************************************************************/

#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    srand(time(NULL));
 
    AVL_TREE avl;

    avl = avl_tree_init_default();

    printf("\n-----CASE 1: LEFT ROTATION-----\n");
    avl_tree_insert(avl, 3, 3);
    avl_tree_insert(avl, 5, 5);
    avl_tree_insert(avl, 7, 7);
    avl_tree_traverse(avl);

    // testing deletion (no output from traverse)
    avl_tree_delete(avl, 7);
    avl_tree_delete(avl, 5);
    avl_tree_delete(avl, 3);

    avl_tree_traverse(avl); // empty traversal becuase of deltion

    avl_tree_destroy(&avl);

    avl = avl_tree_init_default();

    printf("\n-----CASE 2: RIGHT ROTATION-----\n");
    avl_tree_insert(avl, 10, 10);
    avl_tree_insert(avl, 9, 9);
    avl_tree_insert(avl, 8, 8);
    avl_tree_traverse(avl);
    avl_tree_destroy(&avl);

    avl = avl_tree_init_default();

    printf("\n-----CASE 3: LEFT RIGHT ROTATION-----\n");
    avl_tree_insert(avl, 4, 4);
    avl_tree_insert(avl, 10, 10);
    avl_tree_insert(avl, 5, 5);
    avl_tree_traverse(avl);
    avl_tree_destroy(&avl);


    avl = avl_tree_init_default();

    printf("\n-----CASE 4: RIGHT LEFT ROTATION-----\n");
    avl_tree_insert(avl, 10, 10);
    avl_tree_insert(avl, 5, 5);
    avl_tree_insert(avl, 7, 7);
    avl_tree_traverse(avl);
    avl_tree_destroy(&avl);


    avl = avl_tree_init_default();

    printf("\n-----CASE 5: MANY ROTATIONS-----\n");
    avl_tree_insert(avl, 10, 10);
    avl_tree_insert(avl, 9, 9);
    avl_tree_insert(avl, 8, 8);
    avl_tree_insert(avl, 12, 12);
    avl_tree_insert(avl, 7, 7);
    avl_tree_insert(avl, 3, 3); 
    avl_tree_insert(avl, 2, 2);
    avl_tree_insert(avl, 21, 21);
    avl_tree_traverse(avl);
    avl_tree_destroy(&avl);

    printf("\n");

    int input;
   
    printf("Enter 1 for random insertions: ");
    scanf("%d", &input);


    if (input == 1)
    {
        int random_val;
        avl = avl_tree_init_default();

        for(int i = 0; i < 1000; i++)
        {
            random_val = rand();
            avl_tree_insert(avl, random_val, random_val);
        }
        avl_tree_traverse(avl);


        avl_tree_destroy(&avl);
    }
    
    return 0;
}