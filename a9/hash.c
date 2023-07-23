/*
 * your program signature
 */ 

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "hash.h"

extern int htsize;

int hash(char* word) {
  unsigned int hash = 0, i;
  for (i = 0; word[i] != '\0'; i++) {
    hash = 31 * hash + word[i];
  }
  return hash % htsize;
}

HSNODE *new_hashnode(char *key, int value) {
    
    // your implementation
    HSNODE *new_node = (HSNODE *)malloc(sizeof(HSNODE));

    strcpy(new_node->key, key); 
    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

HASHTABLE *new_hashtable(int size) {
    
    // in memory create hashtable
    HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));
    if (ht == NULL) {
        return NULL;
    }

    // arrya oif hashnodes in the memmory
    ht->hna = (HSNODE **)malloc(size * sizeof(HSNODE *));

    // initialize all hash table nodes to NULL
    for (int i = 0; i < size; i++) {
        ht->hna[i] = NULL;
    }

    ht->size = size;
    ht->count = 0;

    return ht;
}

HSNODE *search(HASHTABLE *ht, char *key) {
    int index = hash(key); // Calculate the hash value of the key to get the index

    HSNODE *current_node = ht->hna[index];
    while (current_node != NULL) {
        if (strcmp(current_node->key, key) == 0) {
            // The key is found in the current_node
            return current_node;
        }
        current_node = current_node->next;
    }

    // The key is not found in the hash table
    return NULL;
}


int insert(HASHTABLE *ht, HSNODE *np) {
    
    // 1st: find the hash value (index) of our HashNode key (name)
    int i = hash(strdup(np->key));

    // 2nd: find the index of where we want to insert
    HSNODE *p = ht->hna[i];
    HSNODE *pp = NULL; // our previous pointer

    // General Case: found the index and it is empty
    if (p == NULL){
        ht->hna[i] = np; // set new node as the leading node
    }

    // Special Case: found the index and there is a linked list
    else{
        while (p && strcmp(np->key, p->key) > 0){
            pp = p;
            p = p->next;
        }

        // Case 1: the node already exists in the list
        if (p && strcmp(np->key, p->key) == 0){
            p->value = np->value;
            free(np);
            return 0;
        }
        // Case 2: inserting the node into the 1st position of the list
        if (pp == NULL){
            ht->hna[i] = np; // important
        }
        // Case 3: inserting the node into the nth position of the list; where n > 1
        else{
            pp->next = np;
            np->next = p;
        }
    }
    ht->count++;

    return 1;
}

int delete(HASHTABLE *ht, char *key) {
    if (ht == NULL || key == NULL) {
        return 0; // Invalid input parameters
    }

    int index = hash(key); // Calculate the hash value of the key to get the index

    HSNODE *prev_node = NULL;
    HSNODE *current_node = ht->hna[index];

    while (current_node != NULL) {
        if (strcmp(current_node->key, key) == 0) {
            // Key found, delete the node
            if (prev_node == NULL) {
                // If the node to be deleted is the head of the linked list
                ht->hna[index] = current_node->next;
            } else {
                prev_node->next = current_node->next;
            }

            free(current_node);
            ht->count--;
            return 1; // Successfully deleted the node
        }

        prev_node = current_node;
        current_node = current_node->next;
    }

    // Key not found in the hash table
    return 0;
}


void clean_hash(HASHTABLE **htp) {
  if (*htp == NULL) return;
  HASHTABLE *ht = *htp;
  HSNODE *sp = ht->hna[0], *p, *temp;
  int i;
  for (i = 0; i < ht->size; i++) {
    p = ht->hna[i];
    while (p) {
      temp = p;  
      p = p->next;
      free(temp);
    }
    ht->hna[i] = NULL;
  }
  free(ht->hna);
  ht->hna = NULL;
  *htp = NULL;
}