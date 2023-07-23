#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

HEAP *new_heap(int capacity){

    //1st: create the heap in memory
    HEAP *newHeap = (HEAP *) (malloc(sizeof(HEAP)));

    newHeap->size = 0;
    newHeap->capacity = capacity;
    newHeap->hna = (HNODE*) malloc(sizeof(HNODE) * capacity);

    return newHeap;
}

void insert(HEAP *heap, HNODE new_node)
{
    // your implementation
    // first step, check if the capacity is full; then reallocate space accordingly
    if (heap->size == heap->capacity){

        heap->capacity *= 2; 
            
        HNODE *temp = (HNODE *) malloc(sizeof(HNODE) * heap->capacity);
        if (temp){
            memcpy(temp, heap->hna, sizeof(HNODE) * heap->size);
            free(heap->hna);
            heap->hna = temp;
        } else{
            printf("resize failed\n");
        }
    }

    // second step, we will now insert into the heap
    heap->hna[heap->size] = new_node;
    heapify_up(heap);
    heap->size++;
    return;
}

HNODE extract_min(HEAP *heap) {
    if (heap->size == 0) {
        exit(EXIT_FAILURE);
    }

    // Store the minimum node (root)
    HNODE min_node = heap->hna[0];

    // Move the last node to the root position
    heap->hna[0] = heap->hna[heap->size - 1];
    heap->size--;

    int currentIndex = 0;
    while (1) {
        int leftChild = 2 * currentIndex + 1;
        int rightChild = 2 * currentIndex + 2;
        int smallest = currentIndex;

        // Find the index 
        if (leftChild < heap->size && cmp(heap->hna[leftChild].key, heap->hna[smallest].key) < 0) {
            smallest = leftChild;
        }
        if (rightChild < heap->size && cmp(heap->hna[rightChild].key, heap->hna[smallest].key) < 0) {
            smallest = rightChild;
        }

        // If the root node is the smallest, heap property is maintained
        if (smallest == currentIndex) {
            break;
        }

        // Swap the root node with the smallest child
        HNODE temp = heap->hna[currentIndex];
        heap->hna[currentIndex] = heap->hna[smallest];
        heap->hna[smallest] = temp;

        // Move down to the smallest child level
        currentIndex = smallest;
    }

    return min_node;
}

int change_key(HEAP *heap, int index, KEYTYPE new_key) {
    
    if (index < 0 || index >= heap->size) {
        return 0;  // Return 0 to indicate failure
    }

    heap->hna[index].key = new_key;

    if (index > 0 && heap->hna[index].key < heap->hna[(index-1)/2].key) {
        heapify_up(heap);
    } else {
        heapify_down(heap, index);
    }

    return 1;  // Return 1 to indicate success
}

/**
 * Helper functions below:
 *
*/
int find_data_index(HEAP *heap, DATA data) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->hna[i].data == data) {
            return i; // Found the node with the given data
        }
    }

    return -1; 
}

int cmp(KEYTYPE a, KEYTYPE b) {
    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1; 
    } else {
        return 0; 
    }
}

void swap(HNODE *a, HNODE *b) {
    HNODE tmp = *a;
    *a = *b;
    *b = tmp;
}

HNODE extract_min(HEAP *heap) {
    HNODE min_node = heap->hna[0];
    heap->hna[0] = heap->hna[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return min_node;
}

void heap_sort(HNODE *hna, int n) {
    HEAP heap;
    heap.capacity = n;
    heap.size = n;
    heap.hna = hna;
    
    for (int j = (n-2)/2; j >= 0; j--) {
        heapify_down(&heap, j);
    }
    
    // Extract elements in min-heap order
    for (int i = n-1; i > 0; i--) {
        HNODE temp = hna[0];
        hna[0] = hna[i];
        hna[i] = temp;
        heap.size--;
        heapify_down(&heap, 0);
    }
}

