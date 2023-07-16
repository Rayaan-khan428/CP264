/*
 * your program signature
 */ 
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

// helper functions
TNODE *extract_smallest_node(TNODE **rootp);
int max(int a, int b);

// this is a help function for balance factor.
int height(TNODE *np)
{
    // your implementation
    if (np) {
        return np->height;
    }
    else {
        return 0;
    }
}

int balance_factor(TNODE* np) {
    // your implementation
    if (np) {
        return height(np->left) - height(np->right);
    } else {
        return 0;
    }
}

int is_avl(TNODE *root) {
    // your implementation
    if (root == NULL) { // edge case scenario,
        return 1;
    }

    else {
        // Use recursion to access each node
        int bf = balance_factor(root);
        if (abs(bf) >= 2 || is_avl(root->left) == 0 || is_avl(root->right) == 0) return 0;
        else return 1;
    }
}

TNODE *rotate_right(TNODE *y)
{
    // your implementation
    // 1st: assign pointers
    TNODE *rotatingNode = y->left;
    TNODE *valueNode = rotatingNode->right;

    //2nd: move nodes
    rotatingNode->right = y;
    y->left = valueNode;

    // 3rd: update heights
    rotatingNode->height = 1 + max(height(rotatingNode->left), height(rotatingNode->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return rotatingNode;
}

TNODE *rotate_left(TNODE *x)
{
    // your implementation
    // 1st: assign pointers 
    TNODE *rotatingNode = x->right;
    TNODE *valueNode = rotatingNode->left;

    // 2nd: move nodes
    rotatingNode->left = x;
    x->right = valueNode; 

    // 3rd: update height
    rotatingNode->height = 1 + max(height(rotatingNode->left), height(rotatingNode->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return rotatingNode;

}

// double pointer, we are given a pointer that is pointing to the memory location of the address of root p
void insert(TNODE **rootp, char *name, float score) {

    // 1: create a node
    TNODE *node = (TNODE*) malloc(sizeof(TNODE));
    if (node == NULL){
        return;
    }     
    strcpy(node->data.name, name);
    node->data.score = score;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    // 2: insert node into AVL
    // Edge Case: first node being inserted into avl
    if (*rootp == NULL){
        *rootp = node;
        return;
    }
    
    // Insert the nth node
    TNODE *root = *rootp;
    int cmp = strcmp(name, root->data.name);
    
    // if end has been reached
    if (cmp == 0){
        return;
    }
    // if node is < 1 key
    else if (cmp < 0){
        insert(&root->left, name, score);
    }
    // if the node is > than key
    else if (cmp > 0){
        insert(&root->right, name, score);
    }
    
    // third: update heights
    root->height = ( 1 + max(height(root->left), height(root->right)));
    int bf = balance_factor(root);

    // Case 1: right rotation
    if (bf >= 2){
        if (balance_factor(root->left) >= 0){
            *rootp = rotate_right(root);
        }
        // Case 2: left-right rotation
        else{
            root->left = rotate_left(root->left);
            *rootp = rotate_right(root);
        }
    }
    
    // Case 3: left rotation
    else if (bf <= -2){
        if (balance_factor(root->right) <= 0){
            *rootp = rotate_left(root);
        }
        else{
        // Case 4: right-left rotatation 
        root->right = rotate_right(root->right);
        *rootp = rotate_left(root);
        }
    }

}

void delete(TNODE **rootp, char *name)
{
    TNODE *root = *rootp;
    TNODE* np;

    if (root == NULL) return;

    if (strcmp(name, root->data.name) == 0) {
        if (root->left == NULL && root->right == NULL) {
        free(root);
        *rootp = NULL;
        } else if (root->left != NULL && root->right == NULL) {
        np = root->left;
        free(root);
        *rootp = np;
        } else if (root->left == NULL && root->right != NULL) {
        np = root->right;
        free(root);
        *rootp = np;
        } else if (root->left != NULL && root->right != NULL) {
        np = extract_smallest_node(&root->right);
        np->left = root->left;
        np->right = root->right;
        free(root);
        *rootp = np;
        }
    } else {
        if (strcmp(name, root->data.name) < 0) {
        delete(&root->left, name);
        } else {
        delete(&root->right, name);
        }
    }

        // If the tree had only one node then return
    if (*rootp == NULL) return;

    root = *rootp;
    
    // 2: update the this root node's height
    root->height -= 1;
    
    // 3: get the balance factor of this root node
    int bf = balance_factor(root);

    // 4: re-balance if not balanced
    if (bf >= 2) {

        // case 1: right rotation
        if (balance_factor(root->left) >= 0) {
            *rootp = rotate_right(root);
        } 

        // case 2: left-right rotation
        else {
            root->left = rotate_left(root->left);
            *rootp = rotate_right(root);       
        }

    }

    else if (bf <= -2) {

        // case 3: left-rotation
        if (balance_factor(root->right) <= 0) {
            *rootp = rotate_left(root);
        }

        // case 4: 
        else{
            root->left = rotate_left(root->left);
            *rootp = rotate_right(root);
        }

    }

}


// You are allowed to use the following functions
int max(int a, int b)
{
  return (a > b)? a : b;
}

TNODE *extract_smallest_node(TNODE **rootp) {
  TNODE *tnp = *rootp;
  TNODE *parent = NULL;
  if (tnp == NULL) {
    return NULL;
  } else {
    while (tnp->left) {
      parent = tnp;
      tnp = tnp->left;
    }
    if (parent == NULL)
      *rootp = tnp->right;
    else
      parent->left = tnp->right;
    tnp->left = NULL;
    tnp->right = NULL;
    return tnp;
  }
}

// the following functions are from A7
TNODE *search(TNODE *root, char *name) {
  TNODE *tp = root;
  while (tp) {
    if (strcmp(name, tp->data.name) == 0) {
       return tp;
    } else if (strcmp(name, tp->data.name) < 0) 
      tp = tp->left;
     else 
      tp = tp->right;
  }    
  return NULL;
}

void clean_tree(TNODE **rootp) {
  if (*rootp) {
    TNODE *np = *rootp;
    if (np->left)
      clean_tree(&np->left);
    if (np->right)
      clean_tree(&np->right);
    free(np);
  }
  *rootp = NULL; ;
}