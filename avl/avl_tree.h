#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "status.h"

typedef void* AVL_TREE;

AVL_TREE avl_tree_init_default(void);
Status avl_tree_insert(AVL_TREE, int, int);
int avl_tree_search(AVL_TREE, int, Status*);
void avl_tree_destroy(AVL_TREE*);
void avl_tree_traverse(AVL_TREE);
Status avl_tree_delete(AVL_TREE, int);


#endif
