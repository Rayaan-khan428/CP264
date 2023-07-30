/*
 * Name: Rayaan Khan
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h" 
#include "graph.h"

// Creates a new graph with the given 'order' (number of vertices)
GRAPH *new_graph(int order) {
    int i = 0;

    // Allocate memory for the GRAPH structure
    GRAPH *p = malloc(sizeof(GRAPH));

    // Set the order and size of the graph
    p->order = order;
    p->size = 0;

    // Allocate memory for the array of GNODE pointers to represent the vertices
    p->nodes = malloc(order * sizeof(GNODE*));

    // Initialize each vertex (GNODE) and its neighbor to NULL with a unique node ID (nid)
    for (i = 0; i < order; i += 1) {
        p->nodes[i] = malloc(sizeof(GNODE));
        p->nodes[i]->neighbor = NULL;
        p->nodes[i]->nid = i;
    }

    // Return the pointer to the created GRAPH structure
    return p;
}


// Adds an edge from vertex 'from' to vertex 'to' with the given 'weight' in the graph 'g'
void add_edge(GRAPH *g, int from, int to, int weight) {

    // Variable to keep track if the edge already exists
    int found = 0;

    // Get the neighbor list of the 'from' vertex
    ADJNODE *p = g->nodes[from]->neighbor;

    if (p) {
        // If the neighbor list is not empty, check if the edge already exists
        while (p->next) {
            if (p->nid == to) {
                found = 1;
                break;
            }
            p = p->next;
        }

        // Check the last node in the neighbor list as well
        if (p->nid == to) {
            found = 1;
        }

        if (found) {
            // If the edge already exists, update its weight
            p->weight = weight;
        } else {
            // If the edge doesn't exist, create a new ADJNODE for the 'to' vertex
            ADJNODE *n = malloc(sizeof(ADJNODE));
            n->next = NULL;
            n->nid = to;
            n->weight = weight;
            p->next = n;
        }
    } else {
        // If the neighbor list is empty, create a new ADJNODE for the 'to' vertex
        ADJNODE *n = malloc(sizeof(ADJNODE));
        n->next = NULL;
        n->nid = to;
        n->weight = weight;
        g->nodes[from]->neighbor = n;
    }

    // Increment the graph's size since a new edge has been added
    g->size = g->size + 1;
}


// Displays vertices of the graph in breadth-first order starting from the vertex 'start'
void display_bforder(GRAPH *g, int start) {

    // Create a QUEUE to store vertices to visit in the breadth-first order
    QUEUE queue = {0};

    // Variables to store the current vertex and its neighbors
    GNODE *gnp = NULL;
    ADJNODE *anp = NULL;

    // Check if the graph is NULL, and if so, return (nothing to display)
    if (g == NULL) {
        return;
    }

    // Create an array to keep track of visited vertices
    int n = g->order, visited[n], i;
    for (i = 0; i < n; i += 1) {
        visited[i] = 0;   // Mark all vertices as unvisited
    }

    // Enqueue the starting vertex into the queue
    enqueue(&queue, g->nodes[start]);

    // Mark the starting vertex as visited
    visited[start] = 1;

    // Perform breadth-first traversal using the queue
    while (queue.front) {
        gnp = (GNODE*)dequeue(&queue);  // Dequeue a vertex from the queue
        printf("%d ", gnp->nid);        // Process the current vertex (print its ID)

        // Explore all neighbors (adjacent vertices) of the current vertex
        ADJNODE *p = gnp->neighbor;

        while (p) {
            if (!visited[p->nid]) {
                enqueue(&queue, g->nodes[p->nid]);  // Enqueue unvisited neighbor
                visited[p->nid] = 1;                // Mark neighbor as visited
            }
            p = p->next;  // Move to the next neighbor in the linked list
        }
    }

    // Clean up the queue after traversal
    clean_queue(&queue);
}


// Displays vertices of the graph in depth-first order starting from the vertex 'start'
void display_dforder(GRAPH *g, int start) {

    // Create a STACK to store vertices to visit in the depth-first order
    STACK stack = {0};

    // Variables to store the current vertex and its neighbors
    GNODE *gnp = NULL;
    ADJNODE *anp = NULL;

    // Check if the graph is NULL, and if so, return (nothing to display)
    if (g == NULL) {
        return;
    }

    // Create an array to keep track of visited vertices
    int n = g->order, visited[n], i;

    for (i = 0; i < n; i += 1) {
        visited[i] = 0;   // Mark all vertices as unvisited
    }

    // Push the starting vertex onto the stack
    push(&stack, g->nodes[start]);

    // Mark the starting vertex as visited
    visited[start] = 1;

    // Perform depth-first traversal using the stack
    while (stack.top) {

        gnp = (GNODE*)stack.top->data;
        pop(&stack);   // Pop the top vertex from the stack
        printf("%d ", gnp->nid);   // Process the current vertex (print its ID)

        // Explore all neighbors (adjacent vertices) of the current vertex
        ADJNODE *p = gnp->neighbor;
        while (p) {
            if (!visited[p->nid]) {
                push(&stack, g->nodes[p->nid]);  // Push unvisited neighbor onto the stack
                visited[p->nid] = 1;   // Mark neighbor as visited
            }
            p = p->next;   // Move to the next neighbor in the linked list
        }
    }

    // Clean up the stack after traversal
    clean_stack(&stack);
}


int get_weight(GRAPH *g, int from, int to) {
  
  ADJNODE *p = g->nodes[from]->neighbor;
  int result = INFINITY;
  
  while (p) 
  {
    if (p->nid == to) 
	{
        result = p->weight;
        break;
    }
    p = p->next;
  }
  return result;
}

void clean_graph(GRAPH **gp) {
  int i;
  GRAPH *g = *gp;
  ADJNODE *temp, *ptr;
  for (i = 0; i < g->order; i++) {
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      temp = ptr;
      ptr = ptr->next;
      free(temp);
    }
    free(g->nodes[i]);
  }
  free(g->nodes);
  free(g);
  *gp = NULL;
}

void display_graph(GRAPH *g) {
  if (g == NULL) return;
  printf("order:%d\n", g->order);
  printf("size:%d\n", g->size);
  printf("from:(to weight)");
  int i;
  ADJNODE *ptr;
  for (i = 0; i < g->order; i++) {
    printf("\n%d:", g->nodes[i]->nid);
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      printf("(%d %d) ", ptr->nid, ptr->weight);
      ptr = ptr->next;
    }
  }
}