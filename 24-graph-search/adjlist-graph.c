#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include "contracts.h"

typedef struct adjlist_node adjlist;
struct adjlist_node {
    vertex vert;
    adjlist *next;
};

typedef struct graph_header graph;
struct graph_header {
    unsigned int size;
    adjlist **adj;
};

bool is_vertex(graph *G, vertex v) {
    return G != NULL && v < G->size;
}

bool is_graph(graph *G) {
    if (G == NULL || G->adj == NULL) return false;
    for (unsigned int i = 0; i < G->size; i++) {
        for (adjlist *p = G->adj[i]; p != NULL; p = p->next) {
            if (!is_vertex(G, p->vert)) return false;
            if (p->vert == i) return false; // No self-loops
        }
    }
    return true;
}

graph *graph_new(unsigned int size) 
{
    REQUIRES(size > 0);
    
    graph *G = malloc(sizeof *G);
    G->size = size;
    G->adj = calloc(size, sizeof *G->adj);
    
    ENSURES(is_graph(G));
    return G;
}

void graph_free(graph *G) 
{
    REQUIRES(is_graph(G));
    
    for (unsigned int i = 0; i < G->size; i++) {
        for (adjlist *p = G->adj[i]; p != NULL;) {
            adjlist* prev = p;
            p = p->next;
            free(prev);
        }
    }
    free(G->adj);
    free(G);
}

unsigned int graph_size(graph *G) 
{
    REQUIRES(is_graph(G));
    return G->size;
}

bool graph_hasedge(graph *G, vertex v, vertex w) 
{
    REQUIRES(is_graph(G));
    REQUIRES(is_vertex(G, v)); 
    REQUIRES(is_vertex(G, w));

    for (adjlist *p = G->adj[v]; p != NULL; p = p->next) {
        if (p->vert == w) return true;
    }
    return false;
}

/* Helper to insert neighbors in ASCENDING order to match adjmat behavior */
static void insert_sorted(adjlist **list, vertex v) {
    adjlist *new_node = malloc(sizeof *new_node);
    new_node->vert = v;
    new_node->next = NULL;

    // Case 1: List is empty or new node is smaller than head
    if (*list == NULL || v < (*list)->vert) {
        new_node->next = *list;
        *list = new_node;
    } 
    // Case 2: Insert somewhere in the middle or end
    else {
        adjlist *current = *list;
        while (current->next != NULL && current->next->vert < v) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void graph_addedge(graph *G, vertex v, vertex w) 
{
    REQUIRES(is_graph(G));
    REQUIRES(is_vertex(G, v));
    REQUIRES(is_vertex(G, w));
    REQUIRES(v != w);
    REQUIRES(!graph_hasedge(G, v, w));

    // Insert into v's list (sorted)
    insert_sorted(&G->adj[v], w);
    
    // Insert into w's list (sorted)
    insert_sorted(&G->adj[w], v);

    ENSURES(is_graph(G));
    ENSURES(graph_hasedge(G, v, w));
}
struct neighbor_header {
    adjlist *next_neighbor;
};

typedef struct neighbor_header neighbors;

bool is_neighbors(neighbors *nbors) {
    return nbors != NULL;
}

neighbors *graph_get_neighbors(graph *G, vertex v) 
{
    REQUIRES(is_graph(G));
    REQUIRES(is_vertex(G, v));

    neighbors *nbors = malloc(sizeof *nbors);
    nbors->next_neighbor = G->adj[v];

    ENSURES(is_neighbors(nbors));
    return nbors;
}

bool graph_hasmore_neighbors(neighbors *nbors) 
{
    REQUIRES(is_neighbors(nbors));
    return nbors->next_neighbor != NULL;
}

vertex graph_next_neighbor(neighbors *nbors)
{
    REQUIRES(is_neighbors(nbors));
    REQUIRES(graph_hasmore_neighbors(nbors));

    vertex v = nbors->next_neighbor->vert;
    nbors->next_neighbor = nbors->next_neighbor->next;
    return v;
}

void graph_free_neighbors(neighbors *nbors) {
    REQUIRES(is_neighbors(nbors));
    free(nbors);
}


