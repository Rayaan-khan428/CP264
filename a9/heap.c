#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

HEAP *new_heap(int capacity)
{
// your implementation
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
    if (heap == NULL) {
        exit(EXIT_FAILURE);
    }

    // Set the capacity to at least MIN_CAPACITY
    heap->capacity = (capacity < MIN_CAPACITY) ? MIN_CAPACITY : capacity;
    heap->size = 0;

    // Allocate memory for the heap node array
    heap->hna = (HNODE *)malloc(heap->capacity * sizeof(HNODE));
    if (heap->hna == NULL) {
        free(heap);
        exit(EXIT_FAILURE);
    }

    return heap;
}

void insert(HEAP *heap, HNODE new_node)
{
    // your implementation
    // Check if the heap is full and resize if needed
    if (heap->size == heap->capacity) {
        heap->capacity *= 2; // Double the capacity
        heap->hna = (HNODE *)realloc(heap->hna, heap->capacity * sizeof(HNODE));
        if (heap->hna == NULL) {
            exit(EXIT_FAILURE);
        }
    }

    // Add the new node to the end of the heap
    int currentIndex = heap->size;
    heap->hna[currentIndex] = new_node;
    heap->size++;

    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;
        if (cmp(heap->hna[parentIndex].key, heap->hna[currentIndex].key) <= 0) {
            break;
        }

        // Swap the parent and current nodes
        HNODE temp = heap->hna[parentIndex];
        heap->hna[parentIndex] = heap->hna[currentIndex];
        heap->hna[currentIndex] = temp;

        // Move up to the parent level
        currentIndex = parentIndex;
    }
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
        exit(EXIT_FAILURE);
    }

    if (cmp(new_key, heap->hna[index].key) < 0) {
        // If the new key is smaller, move the node up (percolate-up)
        heap->hna[index].key = new_key;
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (cmp(heap->hna[parentIndex].key, heap->hna[index].key) <= 0) {
                break;
            }

            HNODE temp = heap->hna[parentIndex];
            heap->hna[parentIndex] = heap->hna[index];
            heap->hna[index] = temp;

            // Move up to the parent level
            index = parentIndex;
        }
    } else if (cmp(new_key, heap->hna[index].key) > 0) {
        heap->hna[index].key = new_key;
        while (1) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            // Find the index of the smallest child node
            if (leftChild < heap->size && cmp(heap->hna[leftChild].key, heap->hna[smallest].key) < 0) {
                smallest = leftChild;
            }
            if (rightChild < heap->size && cmp(heap->hna[rightChild].key, heap->hna[smallest].key) < 0) {
                smallest = rightChild;
            }

            // If the node is the smallest, heap property is maintained
            if (smallest == index) {
                break;
            }

            // Swap the node with the smallest child
            HNODE temp = heap->hna[index];
            heap->hna[index] = heap->hna[smallest];
            heap->hna[smallest] = temp;

            // Move down to the smallest child level
            index = smallest;
        }
    }
}


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