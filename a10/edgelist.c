/*
 * Name: Rayaan Khan
 */

#include <stdio.h>

#include <stdlib.h>

#include "edgelist.h"

// Creates a new EDGELIST and initializes its fields
EDGELIST *new_edgelist() {
    // Allocate memory for the EDGELIST structure
    EDGELIST *p = malloc(sizeof(EDGELIST));

    // Initialize the start and end pointers to NULL (empty list)
    p->start = NULL;
    p->end = NULL;

    // Set the initial size of the EDGELIST to 0 (no edges)
    p->size = 0;

    // Return the pointer to the newly created EDGELIST
    return p;
}


// Adds a new edge to the end of the EDGELIST
void add_edge_end(EDGELIST *g, int from, int to, int weight) {
    // Create a new EDGE and allocate memory for it
    EDGE *e = malloc(sizeof(EDGE));

    // Set the properties of the new EDGE
    e->to = to;
    e->from = from;
    e->weight = weight;
    e->next = NULL;

    // Check if the EDGELIST is not empty
    if (g->end) {
        // If the EDGELIST is not empty, add the new EDGE after the current end
        g->end->next = e;
    } else {
        // If the EDGELIST is empty, make the new EDGE the start of the list
        g->start = e;
    }

    // Update the end of the EDGELIST to be the new EDGE
    g->end = e;

    // Increment the size of the EDGELIST since a new edge has been added
    g->size += 1;
}


// Adds a new edge to the start of the EDGELIST
void add_edge_start(EDGELIST *g, int from, int to, int weight) {
    // Create a new EDGE and allocate memory for it
    EDGE *e = malloc(sizeof(EDGE));

    // Set the properties of the new EDGE
    e->to = to;
    e->from = from;
    e->weight = weight;
    e->next = g->start; // Point the next pointer to the current start of the EDGELIST

    // Check if the EDGELIST is empty (no start node)
    if (!g->start) {
        // If the EDGELIST is empty, set the end to be the new EDGE
        g->end = e;
    }

    // Update the start of the EDGELIST to be the new EDGE
    g->start = e;

    // Increment the size of the EDGELIST since a new edge has been added
    g->size = g->size + 1;
}

int weight_edgelist(EDGELIST * g) {
  
  // your implementation
  int weight;
  weight = 0;

  EDGE * p = g -> start;

  while (p) {
    weight = weight + p -> weight;
    p = p -> next;

  }

  return weight;
}

void clean_edgelist(EDGELIST ** gp) {
  EDGELIST * g = * gp;
  EDGE * temp, * p = g -> start;
  while (p) {
    temp = p;
    p = p -> next;
    free(temp);
  }
  free(g);
  * gp = NULL;
}

void display_edgelist(EDGELIST * g) {
  if (g == NULL) return;
  printf("size:%d\n", g -> size);
  printf("(from to weight):");
  EDGE * p = g -> start;
  while (p) {
    printf("(%d %d %d) ", p -> from, p -> to, p -> weight);
    p = p -> next;
  }
}