/*
-------------------------------------------------------
Project:  cp264oc-a7q1
File:     queue_stack.h
About:    header and implementation of queue and stack DS
Author:   HBF
Version:  2023-06-20
-------------------------------------------------------
*/

#ifndef QUEUE_STACK_H
#define QUEUE_STACK_H



// header definitions
typedef struct node {
  void *data;
  struct node *next;
} NODE;

typedef struct queue {
  NODE *front, *rear;
} QUEUE;

void enqueue(QUEUE *qp, void *data);
void *dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);


typedef struct stack {
  NODE *top;
} STACK;

void push(STACK *sp, void *data);
void *pop(STACK *sp);
void clean_stack(STACK *sp);


#endif
