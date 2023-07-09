/*
 * your program signature
 */ 
 
#ifndef MYRECORD_BST_H
#define MYRECORD_BST_H

#include "bst.h"

/* tree type */
typedef struct {
  TNODE *root;
  float count;
  float mean;
  float stddev;   
} TREE;

/* add a record (name, score) into the bst and update the stats info incrementally */
void add_data(TREE *tree, char *name, float score);

/* delete a record of name from the bst and update the stats info incrementally */
void remove_data(TREE *tree, char *name);

#endif