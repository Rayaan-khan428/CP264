/*
 * your program signature
 */ 

#include <stdio.h>
#include <stdlib.h> 
#include "heap.h"
#include "algorithm.h"

EDGELIST *mst_prim(GRAPH *g, int start) {
    // your implementation
    if (g == NULL){
    	return NULL;
    }

    int i, index, n = g->order, T[n], parent[n];

    for (i = 0; i < n; i += 1) {
    	T[i] = 0;
    }

    for (i = 0; i < n; i += 1) {
    	parent[i] = -1;
    }

    HEAPNODE hn;
    HEAP *h = new_heap(4);
    ADJNODE *temp = g->nodes[start]->neighbor;

    T[start] = 1;

    while (temp) {
        hn.key = temp->weight;
        hn.data = temp->nid;

        insert(h, hn);

        parent[temp->nid] = start;
        temp = temp->next;
    }


    EDGELIST *mst = new_edgelist();

    while (h->size > 0) {
        hn = extract_min(h);
        i = hn.data;

        T[i] = 1;

        add_edge_end(mst, parent[i], i, hn.key);

        temp = g->nodes[i]->neighbor;

        while (temp) {
        	index = find_data_index(h, temp->nid);

            if (index >= 0) {
                if (T[temp->nid] == 0 && temp->weight < h->hna[index].key) {
                    change_key(h, index, temp->weight);
                    parent[temp->nid] = i;
                }
            }
            else {
                if (T[temp->nid] == 0) {
                    hn.key = temp->weight;
                    hn.data = temp->nid;

                    insert(h, hn);

                    parent[temp->nid] = i;
                }
            }
            temp = temp->next;
        }
    }
    return mst;

}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {
    // your implementation
    if (!g) {
    	return NULL;
    }

    EDGELIST *spt = new_edgelist();
    HEAPNODE hn;
    HEAP *h = new_heap(4);

    int i, heapindex, x, n = g->order;
    int T[n], label[n], parent[n];

    for (i = 0; i < n; i++) {
    	T[i] = 0; label[i] = 9999;
    }

    label[start] = 0;
    T[start] = 1;

    x = start;

    while((g->order-1) - spt->size != 0){
        ADJNODE *v = g->nodes[x]->neighbor;

        while(v){

            if(label[x]+v->weight < label[v->nid]){

                label[v->nid] = label[x]+v->weight;
                parent[v->nid] = x;

                hn.key = v->weight + label[x];
                hn.data = v->nid;

                insert(h, hn);
            }
            v = v->next;
        }

        if(h->size != 0){
            hn = extract_min(h);

            if(label[hn.data] != 9999){
                x = hn.data;

                T[x] = 1;
                label[x] = hn.key;

                add_edge_end(spt, parent[x], x, label[x]-label[parent[x]]);
            }
        }
    }

    return spt;


}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
    // your implementation
	if (!g) return NULL;
		EDGELIST *spt = new_edgelist();
		HEAPNODE hn;
	    HEAP *h = new_heap(4);

	    int i, heapindex, x, n = g->order;
	    int T[n], parent[n], label[n];

	    for (i = 0; i < n; i++) {
	    	T[i] = 0; label[i] = 9999;
	    }

	    label[start] = 0;
	    T[start] = 1;

	    x = start;

	    while((g->order-1) - spt->size != 0){
	        ADJNODE *v = g->nodes[x]->neighbor;

	        while(v){

	            if(label[x]+v->weight < label[v->nid]){

	                label[v->nid] = label[x]+v->weight;
	                parent[v->nid] = x;

	                hn.key = v->weight + label[x];
	                hn.data = v->nid;

	                insert(h, hn);
	            }

	            v = v->next;
	        }

	        if(h->size != 0){
	            hn = extract_min(h);

	            if(label[hn.data] != 9999){
	            	T[x] = 1;

	                x = hn.data;
	                label[x] = hn.key;

	                add_edge_end(spt, parent[x], x, label[x]-label[parent[x]]);
	            }
	        }
	    }

	    EDGELIST *sp = new_edgelist();

	    i = end;

	    while (i != start) {
	        add_edge_start(sp, parent[i], i, label[i]-label[parent[i]]);
	        i = parent[i];
	    }

	    return sp;

}