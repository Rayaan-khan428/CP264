/*
 * JobID: cp264oc-a4-lab4
 * Name: rayaan khan   
 * ID: 210650310
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myrecord_sllist.h"

/**
 * Search singly linked list by name key.
 * @param SLL *sllp provides the address of a singly linked list structure.
 * @param name Key to search
 * @return Pointer to found node if found; otherwise NULL
 */
NODE *sll_search(SLL *sllp, char *name) {
    
    // your implementation
    NODE *tmp = sllp->start;
    while (tmp != NULL) {
        if (strcmp(tmp->data.name, name) == 0)
        {
            return tmp;
        }
        tmp = tmp->next;
        
    }
    return NULL;
}

/**
 * Insert new record to linked list at the position sorted by record name field.
 * @param @param SLL *sllp provides the address of a singly linked list structure.
 * @param name The name data of new record.
 * @param score The score data of new record
 */
void sll_insert(SLL *sllp, char *name, float score) {
    
    // your implementation
    sllp->length += 1;

    // create a new record
    RECORD *new_record = malloc(sizeof(RECORD));                          // should this be sizeof node or record?
    strcpy(new_record->name, name); // add the name
    new_record->score = score;

    // create a new node that has the new record in it
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = *new_record;
    new_node->next = NULL;
    

    // begin process of finding where the node should be put in
    NODE *curr = sllp->start, *prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->data.name, new_node->data.name) >= 0) {
            break; // if an appropriate place is found break out of while loop
        }
        prev = curr;
        curr = curr->next;
    }

    // this means that the linked list did not exist initially in which case we create one
    if (prev == NULL) {
        sllp->start = new_node;
        new_node->next = curr; // should be null
    }

    // if not empty insert after
    else {
        new_node->next = prev->next; 
        prev->next = new_node;
    }

    return;
   
}

/**
 * Delete a node of record matched by the name key from linked list.
 * @param @param SLL *sllp provides the address of a singly linked list structure.
 * @param name  The key used to find the node for deletion. 
 * @return 1 if deleted a matched node, 0 otherwise. 
 */
int sll_delete(SLL *sllp, char *name) {
    
    // your implementation
    NODE *curr = sllp->start, *prev = NULL;
    int flag = 0; // what we need to return

    while (curr != NULL) {

        if (strcmp(curr->data.name, name) == 0) {
            flag = 1; // tell the program we have a match
            sllp->length -= 1; // decrease the length
            break;
        }

        prev = curr;
        curr = curr->next;

    }
    
    // if the first node is the only node
    if (prev == NULL)
    {
        sllp->start = curr->next;
    }
   
    // update our pointers for our linked list if there are more than one nodes in the linked list
    else
    {
        prev->next = curr->next;
    }
    free(curr);
    return flag;
}

/**
 * Clean singly linked list, delete all nodes. 
 * @param @param SLL *sllp provides the address of a singly linked list structure.
 */
void sll_clean(SLL *sllp) {

    // step 1: go through the entire linked list deleting each node using the free method
    NODE *temp = NULL, *curr = sllp->start;
    while(curr != NULL){
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    // step 2: take sllp methods and update it to null and reset length
    // technically this is all we have to do but run risk of memory leaks
    // without step 1
    sllp->length = 0;
    sllp->start = NULL;
    return;

}