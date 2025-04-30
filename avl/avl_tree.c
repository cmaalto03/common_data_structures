
#include "avl_tree.h"
#include <stdlib.h>
#include <stdio.h>

struct node;    

typedef struct node Node;

struct node
{
    int key;
    int data;
    Node* left;
    Node* right;
    int height;
};

struct avl_tree
{
    Node* root;
};

typedef struct avl_tree Avl_tree;

// utils for insertion
int get_max(int x, int y)
{
    return x > y ? x : y;
}

int get_subtree_height(Node* node)
{
    if (node == NULL)
    {
        return 0;
    }

   return get_max(get_subtree_height(node->right), get_subtree_height(node->left) )+ 1;
}

int get_height(Node* node) {
    return node ? node->height : -1;
}

int get_balance(Node* node) {
    return node ? get_height(node->right) - get_height(node->left) : 0;
}

void update_height(Node* node) {
    
    node->height = get_max(get_height(node->left), get_height(node->right)) + 1;
}

Node* make_node(int key, int data)
{
    Node* pNew = (Node*)malloc(sizeof(Node));

    if (pNew != NULL)
    {
        pNew->key = key;
        pNew->data = data;
        pNew->left = NULL;
        pNew->right = NULL;
        pNew->height = 0;
    }

    return pNew;
}

AVL_TREE avl_tree_init_default(void)
{
    Avl_tree* pAvl_tree = (Avl_tree*)malloc(sizeof(Avl_tree));

    if (pAvl_tree != NULL)
    {
        pAvl_tree->root = NULL;
    }

    return pAvl_tree;

}

void right_rotation(Node** root)
{
    Node* prior_root = *root;
    Node* new_root = prior_root->left;

    prior_root->left = new_root->right;
    new_root->right = prior_root;

    *root = new_root;
    update_height(prior_root);
    update_height(new_root);
}

void left_rotation(Node** root)
{
    Node* prior_root = *root;
    Node* new_root = prior_root->right;

    prior_root->right = new_root->left;
    new_root->left = prior_root;

    *root = new_root;

    update_height(prior_root);
    update_height(new_root);
}

void right_left_rotation(Node** root)
{
    right_rotation(&(*root)->right);
    left_rotation(root);
}

void left_right_rotation(Node** root)
{
    left_rotation(&(*root)->left);
    right_rotation(root);
}

void avl_tree_node_insert(Node** root, int key, int data)
{
    
    if(!(*root))
    {

        *root = (Node*)make_node(key, data);
        return;
    }

    if (key == (*root)->key)
    {
        printf("duplicat\n");
        return;
    }

    if (key > (*root)->key)
    {
        avl_tree_node_insert(&(*root)->right, key, data);

    }
    if (key < (*root)->key)
    {
        avl_tree_node_insert(&(*root)->left, key, data);
    }

    update_height(*root);

    int balance = get_balance(*root);

    // LR Double Rotation + RR
    if (balance == -2)
    {

        int sub_balance = get_balance((*root)->left);
        if (sub_balance == 1)
            left_right_rotation(root);
        
        else
            // Right Rotation
            right_rotation(root);
    }

    // RL Double Rotation + LL
    if (balance == 2)
    {
        int sub_balance = get_balance((*root)->right);

        if (sub_balance == -1)
        {
            right_left_rotation(root);
        }

        else
        {
            // Left Rotation
            left_rotation(root);
        }
    }
}

Status avl_tree_insert(AVL_TREE hAvl_tree, int key, int data)
{
    Avl_tree* pAvl_tree = (Avl_tree*)hAvl_tree;
    
    avl_tree_node_insert(&pAvl_tree->root, key, data);

    return SUCCESS;
}

int avl_tree_node_search(Node* root, int key, Status* pStatus)
{
    if (!root)
    {
        if(pStatus)
            *pStatus = FAILURE;

        return 0xBEEF;
    }

    if (root->key == key)
    {
        if(pStatus)
            *pStatus = SUCCESS;

        return root->key;
    }

    if (key > root->key)
    {
        return avl_tree_node_search(root->right, key, pStatus);
    }

    if (key < root->key)
    {
        return avl_tree_node_search(root->left, key, pStatus);
    }

    // catch all
    else
    {
        *pStatus = FAILURE;
        return 0xBEEF;

    }
}

int avl_tree_search(AVL_TREE hAvl_tree, int key, Status* pStatus)
{
    Avl_tree* pAvl_tree = (Avl_tree*)hAvl_tree;
    
    return avl_tree_node_search(pAvl_tree->root, key, pStatus);
}


Status avl_tree_node_delete(Node** root, int key)
{
    if (!(*root))
    {
        return FAILURE;
    }

    // found, so free the memory, and fix the tree
    if ((*root)->key == key)
    {
        Node* delete_me = *root;
        // can just delete it
        if (delete_me->right == NULL && delete_me->left == NULL)
        {
            free(*root);
            *root = NULL;   // don't forget about dangling pointer !
        }
        // singular child
        else if (!(*root)->left || !(*root)->right) 
        {
            Node* temp = (*root)->left ? (*root)->left : (*root)->right;
            free(*root);
            *root = temp;
        }
        else
        {
            Node* parent = *root;
            Node* successor = (*root)->right;

            while (successor->left != NULL)
            {
                parent = successor;
                successor = successor->left;
            }

            (*root)->key = successor->key;
            (*root)->data = successor->data;

            if (parent->left == successor)
            {
                parent->left = successor->right;
            }
            else
            {
                parent->right = successor->right;
            }

            free(successor);
        }

        if (*root != NULL)
        {
            update_height(*root);

            int balance = get_balance(*root);

            // LR Double Rotation + RR
            if (balance == -2)
            {
                int sub_balance = get_balance((*root)->left);
                if (sub_balance == 1)
                    left_right_rotation(root);
                else
                    // Right Rotation
                    right_rotation(root);
            }

            // RL Double Rotation + LL
            else if (balance == 2)
            {
                int sub_balance = get_balance((*root)->right);

                if (sub_balance == -1)
                {
                    right_left_rotation(root);
                }
                else
                {
                    // Left Rotation
                    left_rotation(root);
                }
            }
        }

        return SUCCESS;
    }

    if (key > (*root)->key)
    {
        return avl_tree_node_delete(&(*root)->right, key);
    }
    else // (key < (*root)->key)
    {
        return avl_tree_node_delete(&(*root)->left, key);
    }
}


Status avl_tree_delete(AVL_TREE hAvl_tree, int key)
{
    Avl_tree* pAvl_tree = (Avl_tree*)hAvl_tree;

    return avl_tree_node_delete(&pAvl_tree->root, key);
}
void avl_tree_node_traverse(Node* root)
{
    if (!root)
        return;

    if (root == NULL)
    {
        printf("Hi\n");
    }

            
    avl_tree_node_traverse(root->left);
    printf("%d  Balance: %d\n", root->key, get_balance(root));

    avl_tree_node_traverse(root->right);
    
}

void avl_tree_traverse(AVL_TREE hAvl_tree)
{
    Avl_tree* pAvl_tree = (Avl_tree*)hAvl_tree;
    avl_tree_node_traverse(pAvl_tree->root);
}

void avl_tree_node_destroy(Node* root)
{
    if (!root)
        return;
    avl_tree_node_destroy(root->left);
    avl_tree_node_destroy(root->right);
    free(root);
}

void avl_tree_destroy(AVL_TREE* phAvl_tree)
{
    Avl_tree* pAvl_tree = (Avl_tree*)*phAvl_tree;
    avl_tree_node_destroy(pAvl_tree->root);
    free(pAvl_tree);
}