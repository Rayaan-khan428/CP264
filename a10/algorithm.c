/*
 * Name: Rayaan Khan
 */ 

#include <stdio.h>
#include <stdlib.h> 
#include "heap.h"
#include "algorithm.h"

EDGELIST *mst_prim(GRAPH *g, int start) {
    
    // Check if the input graph is NULL
    if (g == NULL){
        return NULL;
    }

    int i, index, n = g->order, T[n], parent[n];

    // Initialize arrays T and parent
    // T[i] will be 1 if vertex i is included in the minimum spanning tree, 0 otherwise.
    // parent[i] will store the parent of vertex i in the minimum spanning tree.
    for (i = 0; i < n; i += 1) {
        T[i] = 0;    // Mark all vertices as not included in MST
    }

    for (i = 0; i < n; i += 1) {
        parent[i] = -1;   // Initialize parent array with -1 (indicating no parent)
    }

    // Create a new heap and prepare it with the neighbors of the starting vertex 'start'
    HEAPNODE hn;
    HEAP *h = new_heap(4);
    ADJNODE *temp = g->nodes[start]->neighbor;

    T[start] = 1;   // Mark the starting vertex as included in MST

    while (temp) {
        hn.key = temp->weight;
        hn.data = temp->nid;

        // Insert the neighbor node into the heap along with its weight as the key
        insert(h, hn);

        // Set the parent of the neighbor to be the starting vertex
        parent[temp->nid] = start;

        temp = temp->next;
    }

    // Create a new EDGELIST to store the resulting MST
    EDGELIST *mst = new_edgelist();

    // Loop until the heap is empty (all vertices are included in the MST)
    while (h->size > 0) {
        // Extract the node with the minimum weight from the heap
        hn = extract_min(h);
        i = hn.data;

        T[i] = 1;   // Mark the extracted vertex as included in MST

        // Add an edge to the MST between the parent of the extracted vertex and the vertex itself
        add_edge_end(mst, parent[i], i, hn.key);

        temp = g->nodes[i]->neighbor;

        // Explore all neighbors of the extracted vertex
        while (temp) {
            index = find_data_index(h, temp->nid);

            // If the neighbor node is in the heap
            if (index >= 0) {
                // Check if it is not yet included in MST and the weight from the extracted vertex to this neighbor is smaller
                if (T[temp->nid] == 0 && temp->weight < h->hna[index].key) {
                    // Update the key (weight) in the heap for this neighbor
                    change_key(h, index, temp->weight);
                    // Set the parent of this neighbor to be the extracted vertex
                    parent[temp->nid] = i;
                }
            }
            else {
                // If the neighbor node is not in the heap and not yet included in MST
                if (T[temp->nid] == 0) {
                    hn.key = temp->weight;
                    hn.data = temp->nid;

                    // Insert the neighbor node into the heap along with its weight as the key
                    insert(h, hn);

                    // Set the parent of this neighbor to be the extracted vertex
                    parent[temp->nid] = i;
                }
            }
            temp = temp->next;
        }
    }

    // Return the resulting MST as an EDGELIST
    return mst;
}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {
    // Check if the input graph is NULL
    if (!g) {
        return NULL;
    }

    // Create a new EDGELIST to store the resulting Shortest Path Tree (SPT)
    EDGELIST *spt = new_edgelist();

    // Create a new heap to store nodes during Dijkstra's algorithm
    HEAPNODE hn;
    HEAP *h = new_heap(4);

    int i, heapindex, x, n = g->order;
    int T[n], label[n], parent[n];

    // Initialize arrays T, label, and parent
    // T[i] will be 1 if vertex i is included in the Shortest Path Tree, 0 otherwise.
    // label[i] will store the tentative distance from the starting vertex to vertex i.
    // parent[i] will store the parent of vertex i in the Shortest Path Tree.
    for (i = 0; i < n; i++) {
        T[i] = 0;   // Mark all vertices as not included in SPT
        label[i] = 9999;   // Set the tentative distance for all vertices to a large value (infinity)
    }

    label[start] = 0;   // The distance from the starting vertex to itself is 0
    T[start] = 1;   // Mark the starting vertex as included in the SPT

    x = start;

    // Loop until all vertices are included in the SPT (SPT size is equal to graph order - 1)
    while ((g->order - 1) - spt->size != 0) {
        ADJNODE *v = g->nodes[x]->neighbor;

        // Explore all neighbors of vertex x
        while (v) {
            // Relaxation step: If a shorter path is found from the starting vertex to the neighbor through x
            if (label[x] + v->weight < label[v->nid]) {
                label[v->nid] = label[x] + v->weight;
                parent[v->nid] = x;

                hn.key = v->weight + label[x];
                hn.data = v->nid;

                // Insert the neighbor node into the heap along with its updated distance as the key
                insert(h, hn);
            }
            v = v->next;
        }

        // If the heap is not empty, extract the node with the minimum distance from the heap
        if (h->size != 0) {
            hn = extract_min(h);

            // If the distance to the extracted node is not infinity
            if (label[hn.data] != 9999) {
                x = hn.data;

                T[x] = 1;   // Mark the extracted vertex as included in the SPT
                label[x] = hn.key;

                // Add an edge to the SPT between the parent of the extracted vertex and the vertex itself
                // The weight of the edge will be the difference in distances between the two vertices
                add_edge_end(spt, parent[x], x, label[x] - label[parent[x]]);
            }
        }
    }

    // Return the resulting SPT as an EDGELIST
    return spt;
}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
    // Check if the input graph is NULL
    if (!g) return NULL;

    // Create a new EDGELIST to store the resulting Shortest Path
    EDGELIST *spt = new_edgelist();

    // Create a new heap to store nodes during Dijkstra's algorithm
    HEAPNODE hn;
    HEAP *h = new_heap(4);

    int i, heapindex, x, n = g->order;
    int T[n], parent[n], label[n];

    // Initialize arrays T, label, and parent
    // T[i] will be 1 if vertex i is included in the Shortest Path Tree, 0 otherwise.
    // label[i] will store the tentative distance from the starting vertex to vertex i.
    // parent[i] will store the parent of vertex i in the Shortest Path Tree.
    for (i = 0; i < n; i++) {
        T[i] = 0;   // Mark all vertices as not included in the Shortest Path Tree
        label[i] = 9999;   // Set the tentative distance for all vertices to a large value (infinity)
    }

    label[start] = 0;   // The distance from the starting vertex to itself is 0
    T[start] = 1;   // Mark the starting vertex as included in the Shortest Path Tree

    x = start;

    // Loop until all vertices are included in the Shortest Path Tree (SPT size is equal to graph order - 1)
    while ((g->order - 1) - spt->size != 0) {
        ADJNODE *v = g->nodes[x]->neighbor;

        // Explore all neighbors of vertex x
        while (v) {
            // Relaxation step: If a shorter path is found from the starting vertex to the neighbor through x
            if (label[x] + v->weight < label[v->nid]) {
                label[v->nid] = label[x] + v->weight;
                parent[v->nid] = x;

                hn.key = v->weight + label[x];
                hn.data = v->nid;

                // Insert the neighbor node into the heap along with its updated distance as the key
                insert(h, hn);
            }

            v = v->next;
        }

        // If the heap is not empty, extract the node with the minimum distance from the heap
        if (h->size != 0) {
            hn = extract_min(h);

            // If the distance to the extracted node is not infinity
            if (label[hn.data] != 9999) {
                T[x] = 1;   // Mark the extracted vertex as included in the Shortest Path Tree

                x = hn.data;
                label[x] = hn.key;

                // Add an edge to the Shortest Path Tree between the parent of the extracted vertex and the vertex itself
                // The weight of the edge will be the difference in distances between the two vertices
                add_edge_end(spt, parent[x], x, label[x] - label[parent[x]]);
            }
        }
    }

    // Create a new EDGELIST to store the resulting Shortest Path from start to end
    EDGELIST *sp = new_edgelist();

    i = end;

    // Traverse back from the destination vertex to the start vertex to construct the Shortest Path
    while (i != start) {
        add_edge_start(sp, parent[i], i, label[i] - label[parent[i]]);
        i = parent[i];
    }

    // Return the resulting Shortest Path as an EDGELIST
    return sp;
}
