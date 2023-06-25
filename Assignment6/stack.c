#include <stdio.h>
#include "stack.h"


// follows a lifo system (last in first out)

/*
 * push NODE *np onto STACK *sp, and maintain the height property
 */ 
void push(STACK *sp, NODE *np) {
    
    // your implementation
    sp->height += 1;

    // edge case: stack is initially empty
    if (sp->top == NULL) {
        sp->top = np;
    }

    // for rest of the scenarios
    else {
        np->next = sp->top;
        sp->top = np;
    }

}

/*
 * pop and return the pointer to the removed top node, maintain the height property.
 */ 
NODE *pop(STACK *sp) {
    
    // your implementation
    NODE *tmp;

    // edge case: stack is empty
    if (sp->top == NULL) return NULL;

    // stack only has one node
    else if (sp->top->next == NULL) {
        sp->height = 0;
        tmp = sp->top;
        sp->top = NULL;
        return tmp;
    }

    // stack is normal
    else {

        sp->height -= 1;
        tmp = sp->top;
        sp->top = sp->top->next;
        return tmp;

    }

}

/*
 * clean the link list and reset the height
 */ 
void stack_clean(STACK *sp) {
    // your implementation,  
    // call clean() function in common.h
    clean(&sp->top);
}