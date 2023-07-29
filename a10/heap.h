/*
--------------------------------------------------
Project: cp264-a9q3
File:    heap.h
Description: header of heap ds
Author:  HBF  
Version: 2023-03-16
--------------------------------------------------
*/

#ifndef HEAP_H
#define HEAP_H
 
#define MIN_CAPACITY 4

typedef int KEYTYPE;  // key type
typedef int DATA;     // data type 

typedef struct heap_node { // data element ds for binary heap
  KEYTYPE key;
  DATA data;
} HEAPNODE;

typedef struct heap {  
  unsigned int capacity; // the MAX length of array
  unsigned int size;     // the current heap size, i.e., heap node count
  HEAPNODE *hna;  // pointer pointing the heap node array
} HEAP;


HEAP *new_heap(int capacity);
void clean_heap(HEAP **hpp);
void insert(HEAP *heap, HEAPNODE a);
HEAPNODE extract_min(HEAP *heap);
int change_key(HEAP *heap, int index, KEYTYPE new_key);
int find_data_index(HEAP *heap, DATA data);
int cmp(KEYTYPE a, KEYTYPE b); 


#endif 