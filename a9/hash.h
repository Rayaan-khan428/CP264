/*
 * your program signature
 */ 
#ifndef HASH_H
#define HASH_H

typedef struct hashnode {
  char key[10];
  int value;
  struct hashnode *next; 
} HSNODE;

typedef struct hashtable {
  HSNODE **hna; 
  int size; 
  int count;
} HASHTABLE;

int hash(char *key); 
HSNODE *new_hashnode(char *key, int value); 
HASHTABLE *new_hashtable(int size); 
HSNODE *search(HASHTABLE *ht, char *key);
int insert(HASHTABLE *ht, HSNODE *np);
int delete(HASHTABLE *ht, char *key);
void clean_hash(HASHTABLE **ht);

#endif