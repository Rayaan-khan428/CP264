/*
--------------------------------------------------
Project: cp264-a6q3
File:    heap.c
Description: implementation of heap.h
Author:  HBF  
Version: 2023-03-15
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

HEAP *new_heap(int capacity)
{
  HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
  if (hp == NULL) return NULL;
  hp->hna = (HEAPNODE *) malloc(sizeof(HEAPNODE) * capacity);
  if ( hp->hna == NULL) { free(hp); return NULL; };

  hp->capacity = capacity;
  hp->size = 0;
  return hp;
}

void clean_heap(HEAP **hpp) {
   HEAP *hp = *hpp;
   free(hp->hna);
   hp->capacity = 0;
   hp->size = 0;
   free(hp);
   *hpp = NULL;
}

int heapify_up(HEAPNODE *hna, int index) {
  int parent; 
  HEAPNODE temp;
  while (index > 0) {
    parent = (index - 1) >> 1;
    if (cmp(hna[parent].key, hna[index].key)<=0) break;
	else {
	  temp = hna[index];
      hna[index] = hna[parent];
	  hna[parent] = temp;
	  index = parent;
	}
  }
  return index;
}

int heapify_down(HEAPNODE *hna, int n, int index) {
  int child; 
  HEAPNODE temp;
  while (index < n) {
    child = (index << 1) + 1;
    if (child >= n) break;
    if ((child + 1 < n) && cmp(hna[child + 1].key, hna[child].key)<=0) child++;
    if (cmp(hna[index].key, hna[child].key)<=0) break;
	temp = hna[index];
	hna[index] = hna[child];
	hna[child] = temp;
	index = child;
  }
  return index;
}

void insert(HEAP *heap, HEAPNODE new_node)
{
  // Double the array length if it is overflow. 
  if (heap->size == heap->capacity)
  {
    heap->capacity <<= 1;
    HEAPNODE *temp = realloc(heap->hna, sizeof(HEAPNODE) * heap->capacity);
      if (temp) {
      heap->hna = temp;
    } else {
      temp = malloc(sizeof(HEAPNODE) * heap->capacity);
      if (temp) {
        memcpy(temp, heap->hna, sizeof(HEAPNODE) * heap->size);
        free(heap->hna);
        heap->hna = temp;
      } else {
        printf("memory expansion failed\n");
        exit(1);
      }
    }
  }
  
  int index = heap->size;
  heap->hna[index] = new_node;
  heapify_up(heap->hna, index);
  heap->size++;
}

HEAPNODE extract_min(HEAP *heap)
{
  HEAPNODE top = heap->hna[0];
  heap->size = heap->size - 1;
  heap->hna[0] = heap->hna[heap->size];
  heapify_down(heap->hna, heap->size, 0);  
  // Shrink the array to a 1/2 if size <= capacity / 4
  if ((heap->size <= (heap->capacity >> 2)) && (heap->capacity > MIN_CAPACITY)) {
    heap->capacity >>= 1;
    heap->hna = realloc(heap->hna, sizeof(HEAPNODE) * heap->capacity);
  }
  return top;
}

int change_key(HEAP *heap, int index, KEYTYPE new_key)
{
  KEYTYPE temp_key = heap->hna[index].key;
  heap->hna[index].key = new_key; 
  if ( temp_key > new_key) { 
    index = heapify_up(heap->hna, index);
  } else if ( temp_key < new_key) { 
    index = heapify_down(heap->hna, heap->size, index);
  } 
  return index;
}

int find_data_index(HEAP *heap, DATA data) {
  int i, r = -1;
  for (i=0; i<heap->size; i++) {
    if (heap->hna[i].data == data) {r = i; break;}
  }
  return r;
}

int cmp(KEYTYPE a, KEYTYPE b) {
  int r = 0;
  if (a < b) r = -1;
  else if (a > b) r = 1;
  return r;
}

