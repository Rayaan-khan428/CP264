#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"

// adheres to FIFO (first in first out)


/* 
 * enqueue a NODE *np and maintain the length property of the Queue. 
*/
void enqueue(QUEUE *qp, NODE *np) {
    // your implementation

    // edge case, if queue is empty
    if (qp->front == NULL) {
        qp->front = np;
        qp->rear = np;
        qp->length = 1;
    }

    // if queue is not empty
    else {
        qp->rear->next = np;
        qp->rear = np;
        qp->length += 1;
    }     
}  

/* 
 * dequeue and return the pointer of the removed NODE, maintain length property.
*/
NODE *dequeue(QUEUE *qp) {
    
    NODE *tmp;

    // edge case, if queue is empty
    if (qp->front == NULL) return NULL;
    
    // if queue only has one node
    else if (qp->front == qp->rear) {
        tmp = qp->front;
        qp->front = NULL;
        qp->rear = NULL;
        qp->length = 0;
        return tmp;
    }

    // queue has more than one node
    else {
        tmp = qp->front;
        qp->front = qp->front->next;
        qp->length -= 1;
        return tmp;
    }

}

/* 
 * clean the linked list and reset the length
*/
void queue_clean(QUEUE *qp) {
    // your implementation
    // call clean() function in common.h
    clean(&qp->front);

}   
