#include "graph.h"

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

static bool is_vertex(graph *G, vertex v) {
	return G != NULL
			&& v < G->size;
}

static bool is_graph(graph *G) {
	if (G == NULL || G->adj == NULL) return false;
	for (unsigned int i = 0; i < G->size; i++) {
		for (adjlist *p = G->adj[i]; p != NULL; p = p->next) {
			if (!is_vertex(G, p->vert)) return false;
			if (p->vert == i) return false;
		}
	}
	return true;
}

graph *graph_new(unsigned int size) 
//@ensures is_graph(\result);
{
	if (size == 0) {
		fprintf(stderr, "graph_new: size must be > 0\n");
		exit(EXIT_FAILURE);
	}
	graph *G = malloc(sizeof *G);
	G->size = size;
	G->adj = calloc(size, sizeof *G->adj);
	return G;
}

bool graph_hasedge(graph *G, vertex v, vertex w) 
//@requires is_graph(G) && is_vertex(G, v) && is_vertex(G, w);
{
	for (adjlist *p = G->adj[v]; p != NULL; p = p->next) {
		if (p->vert == w) return true;
	}
	return false;
}

void graph_addedge(graph *G, vertex v, vertex w) 
//@requires is_graph(G) && is_vertex(G, v) && is_vertex(G, w);
//@requires v != w && !graph_hasedge(G, v, w);
//@ensures is_graph(G) && graph_hasedge(G, v,w);
{
	adjlist *new_edge;

	new_edge = malloc(sizeof *new_edge);
	new_edge->vert = v;
	new_edge->next = G->adj[w];
	G->adj[w] = new_edge;

	new_edge = malloc(sizeof *new_edge);
	new_edge->vert = w;
	new_edge->next = G->adj[v];
	G->adj[v] = new_edge;
}

struct neighbor_header {
	adjlist *next_neighbor;
};
typedef struct neighbor_header neighbors;

bool is_neighbors(neighbors *nbors) {
	return nbors != NULL;
}

neighbors *graph_get_neighbors(graph *G, vertex v) 
//@requires is_graph(G) && is_vertex(G, v);
//@ensures is_neighbors(\result);
{
	neighbors *nbors = malloc(sizeof *nbors);
	nbors->next_neighbor = G->adj[v];
	return nbors;
}

bool graph_hasmore_neighbors(neighbors *nbors) 
//@requires is_neighbors(nbors);
{
	return nbors->next_neighbor != NULL;
}

vertex graph_next_neighbor(neighbors *nbors)
//@requires is_neighbors(nbors);
//@requires graph_has_more_neighbors(nbors);
{
	vertex v = nbors->next_neighbor->vert;
	nbors->next_neighbor = nbors->next_neighbor->next;
	return v;
}

void graph_free_neighbors(neighbors *nbors) {
	free(nbors);
}


