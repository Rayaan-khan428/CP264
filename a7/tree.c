/*
 * your program signature
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"

TNODE *new_node(int value) {
  TNODE *np = (TNODE *) malloc(sizeof(TNODE));
  if (np != NULL) {
    np->data = value;
    np->left = NULL;
    np->right = NULL;
  }
  return np;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

/* 
 * This computes and returns TPROPS value containing the number of nodes and height 
 * of tree passed by root address. 
*/
TPROPS get_props(TNODE *root) {
    // your implementation
    TPROPS props = {0};
    if (!root)
        return props;
    TPROPS left_props = get_props(root->left);
    TPROPS right_props = get_props(root->right);
    props.height = 1 + max(left_props.height, right_props.height);
    props.order = 1 + left_props.order + right_props.order;
    return props;
}

/* this displays the node data of the tree in pre-order. */
void display_preorder(TNODE *root) {
    // your implementation
    if (root) {
        printf("%c ", root->data);
        display_preorder(root->left);
        display_preorder(root->right);
    }
}

/* this displays the node data of the tree in in-order. */
void display_inorder(TNODE *root) {
    // your implementation
    if (root) {
        display_inorder(root->left);
        printf("%c ", root->data);
        display_inorder(root->right);
    }
}

/* this displays the node data of the tree in post-order. */
void display_postorder(TNODE *root) {
    // your implementation
    if (root) {
        display_postorder(root->left);
        display_postorder(root->right);
        printf("%c ", root->data);
    }
}

/* use auxiliary queue data structure for the algorithm  */
void display_bforder(TNODE *root) {
    // your implementatio
    QUEUE q = {0};
    enqueue(&q, root);
    while (q.front) {
        TNODE *node = (TNODE *) dequeue(&q);
        enqueue(&q, node->left);
        enqueue(&q, node->right);
        printf("%c ", node->data);
    }
}

/* this does the breadth-first-search using an auxiliary queue. */
TNODE *iterative_bfs(TNODE *root, int val) {
    // your implementation
    QUEUE q = {0};
    enqueue(&q, root);
    while (q.front) {
        TNODE *node = (TNODE *) dequeue(&q);
        enqueue(&q, node->left);
        enqueue(&q, node->right);
        if (node->data == val)
            return node;
    }
    return NULL;
}


/* this does the depth-first-search using an auxiliary stack */
TNODE *iterative_dfs(TNODE *root, int val) {
    STACK stack = {0};
    push(&stack, root);
    while(stack.top) {
        TNODE *node = (TNODE *) pop(&stack);
        push(&stack, node->left);
        push(&stack, node->right);
        if (node->data == val)
            return node;
    }
    return NULL;
}


// the following functions are given, need to add to your program.

void clean_tree(TNODE **rootp) {
  TNODE *p = *rootp;
  if (p) {
    if (p->left)
      clean_tree(&p->left);
    if (p->right)
      clean_tree(&p->right);
    free(p);
  }
  *rootp = NULL;
}

void insert_complete(TNODE **rootp, int val){
  if( *rootp == NULL) { 
    *rootp = new_node(val);
  } else {
    QUEUE queue = {0};
    TNODE *p;
    enqueue(&queue, *rootp);
    while(queue.front){
      p = dequeue(&queue);
      if(p->left == NULL){
        p->left = new_node(val);
        break;
      } else {
        enqueue(&queue, p->left);
      }
      
      if(p->right == NULL){
        p->right = new_node(val);
        break;
      } else  {
        enqueue(&queue, p->right);
      }
    }
  }
}