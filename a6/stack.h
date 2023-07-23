#ifndef STACK_H
#define STACK_H

#include "common.h"

typedef struct stack {
  int height;
  NODE *top;
} STACK;

void push(STACK *sp, NODE *np);
NODE *pop(STACK *sp);
void stack_clean(STACK *sp);

#endif