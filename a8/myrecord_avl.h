/*
 * your program signature
 */ 
 
 
#ifndef MYRECORD_AVL_H
#define MYRECORD_AVL_H

#include "avl.h"

typedef struct tree {
    TNODE *root;
    float count;
    float mean;
    float stddev;
} TREE;

/* merge tree rootp2 into tree rootp1 */
void merge_tree(TNODE **rootp1, TNODE **rootp2); 

/* merget data tree t2 to data tree t1 */
void merge_data(TREE *t1, TREE *t2);

// the following are adapted/modified from A7
void add_data(TREE *tree, char *name, float score);
void remove_data(TREE *tree, char *name);

#endif