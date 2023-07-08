/*
-------------------------------------------------------
Project:  cp264oc-a7q1
File:     queue_stack.h
About:    header and implementation of queue and stack DS
Author:   HBF
Version:  2023-06-20
-------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

#include "queue_stack.h"


// implementation
void enqueue(QUEUE *qp, void *data) {
   if (qp== NULL || data == NULL) return;	
   NODE *p = (NODE*) malloc(sizeof(NODE));
   if (p != NULL) { 
     p->data = data;
     p->next = NULL;
     
     if (qp->front == NULL) {
      qp->front = p;
      qp->rear = p;
     } else {
      (qp->rear)->next = p;
      qp->rear = p; 
    }
  }
}

void *dequeue(QUEUE *qp) {	
  void *r = NULL;
  if (qp != NULL && qp->front) {
    NODE *p = qp->front;
    r = p->data;
    if (qp->front == qp->rear) {
      qp->front = NULL;
      qp->rear = NULL;
    } else {
      qp->front = p->next;
    }
    free(p);  
  }
  return r;
}

void clean_queue(QUEUE *qp) {
  if (qp==NULL) return;	
  NODE *temp, *p = qp->front; 
  while (p != NULL) {
    temp = p;
    p = p->next;
    free(temp);
  }
  qp->front = NULL;
  qp->rear = NULL;
}


void push(STACK *sp, void *data) {
  if (sp== NULL || data == NULL) return;	
  NODE *p = (NODE*) malloc(sizeof(NODE));
  if (p != NULL) { 
    p->data = data;
    p->next = NULL;
    if (sp->top == NULL) {
      sp->top = p;
    } else {
      p->next = sp->top;
      sp->top = p;
    }
  }
}

void *pop(STACK *sp) {
  void *r = NULL;	
  if (sp != NULL && sp->top) {
    NODE *p = sp->top;
	r = p->data;
    sp->top = p->next;
    free(p);
  }
  return r;
}

void clean_stack(STACK *sp) {
 if (sp == NULL) return;	
  NODE *temp, *p = sp->top;
  while (p) {
    temp = p;
    p = p->next;
    free(temp);
  }
  sp->top = NULL;
}

