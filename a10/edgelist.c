/*
 * your program signature
 */ 

#include <stdio.h>
#include <stdlib.h> 
#include "edgelist.h"

EDGELIST *new_edgelist() {

  // your implementation
	EDGELIST *p = malloc(sizeof(EDGELIST));

	p->size = 0;
	p->start = NULL;
	p->end = NULL;

	return p;


}

void add_edge_end(EDGELIST *g, int from, int to, int weight) {
  // your implementation
  EDGE *e = malloc(sizeof(EDGE));

	e->to = to;
	e->from = from;
	e->weight = weight;
	e->next = NULL;

	if(g->end){
		g->end->next = e;
	}

	else{
		g->start = e;
	}

	g->size += 1;
	g->end = e;
}

void add_edge_start(EDGELIST *g, int from, int to, int weight) {
  // your implementation
	EDGE *e = malloc(sizeof(EDGE));

	e->to = to;
	e->from = from;
	e->weight = weight;
	e->next = g->start;

	if(! g->start){
		g->end = e;
	}

	g->start = e;
	g->size += 1;
}

int weight_edgelist(EDGELIST *g) {
  // your implementation
  int weight = 0;

	EDGE *p = g->start;

	while (p){
		weight += p->weight;
		p = p->next;

	}

	return weight;
}

void clean_edgelist(EDGELIST **gp) {
  EDGELIST *g = *gp;
  EDGE *temp, *p = g->start;
  while (p) {
    temp = p;
    p = p->next;
    free(temp);
  }
  free(g);
  *gp = NULL;
}

void display_edgelist(EDGELIST *g) {
  if (g == NULL) return;
  printf("size:%d\n", g->size);
  printf("(from to weight):");
  EDGE *p = g->start;
  while (p) {
    printf("(%d %d %d) ", p->from, p->to, p->weight);
    p = p->next;
  }
}