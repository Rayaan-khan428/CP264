/*
 * your program signature
 */ 
 
#ifndef HEAP_H
#define HEAP_H
 
#define MIN_CAPACITY 4

typedef int KEYTYPE;
typedef int DATA;

typedef struct heap_node {
  KEYTYPE key;
  DATA data;
} HNODE;

typedef struct heap {  
  unsigned int capacity; 
  unsigned int size; 
  HNODE *hna; 
} HEAP;


HEAP *new_heap(int capacity);
void insert(HEAP *heap, HNODE a);
HNODE extract_min(HEAP *heap);
int change_key(HEAP *heap, int index, KEYTYPE new_key);
int find_data_index(HEAP *heap, DATA data);
int cmp(KEYTYPE a, KEYTYPE b);  
 
#endif 
