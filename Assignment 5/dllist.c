#include <stdio.h>
#include <stdlib.h> 
#include "dllist.h"

NODE *new_node(char data) {
    
    // your implementation
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;

}

/*
 * This inserts a node at the beginning the of a doubly linked list. 
*/
void dll_insert_start(DLL *dllp, NODE *np) {
    
    // Check if the doubly linked list is empty
    if (dllp->start == NULL) {
        dllp->start = np;
        dllp->end = np;
        np->prev = NULL;
        np->next = NULL;
    } else {
        np->prev = NULL;
        np->next = dllp->start;
        dllp->start->prev = np;
        dllp->start = np;
    }

    dllp->length++;
}


void dll_insert_end(DLL *dllp, NODE *np) {
    
    // your implementation
    np->prev = dllp->end;
    dllp->end->next = np;
    dllp->end = np;
    dllp->length += 1;

}

void dll_delete_start(DLL *dllp) {
    
    if (dllp->start == NULL) {
        return; // Nothing to delete
    }

    NODE *current = dllp->start; // current start node

    dllp->start = current->next; // Update the start pointer to the next node

    if (dllp->start != NULL) {
        dllp->start->prev = NULL; // Update the prev pointer of the new start node
    } 
    
    else {
        dllp->end = NULL; // update the end pointer
    }

    free(current); // Free memory 

    dllp->length -= 1; // Update the length of the doubly linked list
}


void dll_delete_end(DLL *dllp) {
    
    // your implementation

    // checking if empty
    if (dllp->start == NULL) {
        return;
    }

    // if there is only one node in the doubly linked list
    if (dllp->start == dllp->end) {
        free(dllp->start);
        dllp->start = NULL;
        dllp->end = NULL;
        dllp->length = 0;
        return;
    }

    // Update the prev pointer of the second-to-last node
    dllp->end->prev->next = NULL;

    // Update the end pointer
    dllp->end = dllp->end->prev;

    // Free the memory
    free(dllp->end->next);

    // Update length 
    dllp->length -= 1;

}

void dll_clean(DLL *dllp) {
    
    dllp->length = 0;

    NODE *curr = dllp->start;
    NODE *next;

    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    dllp->start = NULL;
    dllp->end = NULL;
    
}

