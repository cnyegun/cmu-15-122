#include "graph.h"
#include "contracts.h"

typedef struct graph_header graph;
struct graph_header {
	unsigned int size;
	bool *adj;
};

bool is_vertex(graph* G, vertex v) {
	return G != NULL
			&& v < G->size;
}

bool is_graph(graph *G) {
	if (G == NULL || G->adj == NULL) return false;

	// Check no self-edges
	for (unsigned int i = 0; i < G->size; i++) {
		for (unsigned int j = 0; j < G->size; j++) {
			// False if a node has edge to itself
			if (i == j && G->adj[(size_t) G->size*i + j] == true) return false;
		}
	}
	return true;
}

graph* graph_new(unsigned int numvert)
{
	REQUIRES(numvert > 0);
	graph *G = malloc(sizeof *G);
	G->size = numvert;
	G->adj = calloc((size_t) numvert * numvert, sizeof *G->adj);
	ENSURES(G != NULL);
	return G;
}
void graph_free(graph *G)
{
	REQUIRES(G != NULL);
	free(G->adj);
	free(G);
}
unsigned int graph_size(graph *G)
{
	REQUIRES(G != NULL);
	return G->size;
}

bool graph_hasedge(graph* G, vertex v, vertex w)
{
	REQUIRES(G != NULL);
	REQUIRES(v < graph_size(G) && w < graph_size(G));
	return G->adj[(size_t) v*G->size + w];
}

void graph_addedge(graph* G, vertex v, vertex w)
{
	REQUIRES(G != NULL);
	REQUIRES(v < graph_size(G) && w < graph_size(G));
	REQUIRES(v != w && !graph_hasedge(G, v, w));

	G->adj[(size_t) v*G->size + w] = true;
	G->adj[(size_t) w*G->size + v] = true;

	ENSURES(graph_hasedge(G, v, w));
}

typedef struct neighbor_header neighbors;
struct neighbor_header {
	graph *origin_graph;
	unsigned int vert;
	unsigned int pos_v;
	unsigned int pos_w;
};

neighbors *graph_get_neighbors(graph* G, vertex v)
{
	REQUIRES(G != NULL);
	REQUIRES(v < graph_size(G));

	neighbors *nbors = malloc(sizeof *nbors);
	nbors->origin_graph = G;
	nbors->vert = v;
	nbors->pos_v = v;
	nbors->pos_w = 0;

	ENSURES(nbors != NULL);
	return nbors;
	return nbors;
}

bool graph_hasmore_neighbors(neighbors *nbors)
{
	REQUIRES(nbors != NULL);

	for (unsigned int i = nbors->pos_w; i < nbors->origin_graph->size; i++) {
		if (graph_hasedge(nbors->origin_graph, nbors->pos_v, i))
			return true;
	}
	return false;
}

vertex graph_next_neighbor(neighbors *nbors) {
	REQUIRES(nbors != NULL);
	REQUIRES(graph_hasmore_neighbors(nbors));

	for (unsigned int i = nbors->pos_w; i < nbors->origin_graph->size; i++) {
		if (graph_hasedge(nbors->origin_graph, nbors->pos_v, i)) {
			nbors->pos_w = i + 1;
			return i;
		}
	}
}

void graph_free_neighbors(neighbors *nbors) {
	REQUIRES (nbors != NULL);
	free(nbors);
}
