#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

typedef struct queue {
  int length;
  NODE *front;
  NODE *rear;
} QUEUE;    

void enqueue(QUEUE *qp, NODE *np);
NODE *dequeue(QUEUE *qp);
void queue_clean(QUEUE *qp);

#endif
