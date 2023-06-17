/*
 * JobID: cp264oc-a4-lab4
 * Name: rayaan khan   
 * ID: 210650310
 */ 
 
#ifndef SLL_H
#define SLL_H

typedef struct {
  char name[40];
  float score;
} RECORD;

typedef struct node {
  RECORD data;
    struct node *next;
} NODE;

typedef struct sllist {
  int length;
    NODE *start;
} SLL;


NODE *sll_search(SLL *sllp, char *name);
void sll_insert(SLL *sllp, char *name, float score);
int sll_delete(SLL *sllp,  char *name);
void sll_clean(SLL *sllp);

#endif