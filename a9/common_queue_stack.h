/*--------------------------------------------------
Project: cp264oc-a9q2
File:    common_queue_stack.h
About:   header of node structure and functions for linked list queue and stack for expression
Author:  HBF  
Version: 2023-06-21
--------------------------------------------------
*/
#ifndef COMMON_QUEUE_STACK_H
#define COMMON_QUEUE_STACK_H

/* node structure for postfix expression by queue and evaluation by stack */ 
typedef struct node {
	int data;  // int data is used for int operand, operator ascii code, or parenthesis assii code 
	int type;  // 0: int operand; 1:operator; 2: left parenthesis 3: right parenthesis 
	struct node *next;
} NODE;
NODE *new_node(int data, int type);
void display(NODE *start);
void clean(NODE **startp);

// queue
typedef struct queue {
  int length;
  NODE *front;
  NODE *rear;
} QUEUE;	
void enqueue(QUEUE *qp, NODE *np);
NODE *dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);

// stack
typedef struct stack {
  int height;
  NODE *top;
} STACK;
void push(STACK *sp, NODE *np);
NODE *pop(STACK *sp);
void clean_stack(STACK *sp);

#endif
