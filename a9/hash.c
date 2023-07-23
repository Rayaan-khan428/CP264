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
    // if (new_node == NULL) {
    //     return NULL;
    // }

    strncpy(new_node->key, key, 10); // Copy at most 10 characters of the key to the new node
    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

HASHTABLE *new_hashtable(int size) {
    HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));
    if (ht == NULL) {
        return NULL;
    }

    ht->hna = (HSNODE **)malloc(size * sizeof(HSNODE *));
    if (ht->hna == NULL) {
        free(ht);
        return NULL;
    }

    // Initialize all hash table nodes to NULL
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
    if (ht == NULL || np == NULL) {
        return 0; // Invalid input parameters
    }

    int index = hash(np->key); // Calculate the hash value of the key to get the index

    // Check if the key already exists in the hash table
    HSNODE *existing_node = search(ht, np->key);
    if (existing_node != NULL) {
        // Key already exists, update the value
        existing_node->value = np->value;
        return 1; // Successfully updated the value
    }

    // Key does not exist, insert a new node at the beginning of the linked list
    np->next = ht->hna[index];
    ht->hna[index] = np;
    ht->count++;

    return 1; // Successfully inserted the new node
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