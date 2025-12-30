#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "contracts.h"
#include "queue.h"

// size of *mark array: graph_size(G);

bool bfs(graph_t G, vertex start, vertex target) {
	REQUIRES (G != NULL);
	REQUIRES(start < graph_size(G) && target < graph_size(G));

	// Special case: start == target
	if (start == target) return true;	
		
	// We need a array to check visited vertex
	bool *mark = calloc(graph_size(G), sizeof *mark);
	// We are in the start node
	mark[start] = true;

	// Create a worklist 
	queue_t worklist = queue_new();	
	// Init with our starting vertex
	enq(worklist, start);
	
	// Do this until nothing left in the worklist 
	while (!queue_empty(worklist)) {
		vertex v = deq(worklist);
		if (v == target) {
			queue_free(worklist);
			free(mark);
			return true;
		}

		// * This is not the target we are looking for
		// Append all the unknown neighbors of this node
		neighbors_t nbors = graph_get_neighbors(G, v);
		while (graph_hasmore_neighbors(nbors)) {
			vertex w = graph_next_neighbor(nbors);
			if (!mark[w]) {
				enq(worklist, w);
				mark[w] = true;
			}
		}
		graph_free_neighbors(nbors);
	}

	// There is no path
	free(mark);
	queue_free(worklist);
	return false;
}

int main() {
	graph_t G = graph_new(6);
	// A = 0; B = 1; C = 2; D = 3; E = 4
	graph_addedge(G, 0, 1);
	graph_addedge(G, 0, 4);
	graph_addedge(G, 1, 2);
	graph_addedge(G, 1, 4);
	graph_addedge(G, 4, 2);
	graph_addedge(G, 2, 3);

	assert(bfs(G, 3, 2));
	assert(bfs(G, 1, 3));
	assert(!bfs(G, 0, 5));
	printf("All tests passed!\n");
	graph_free(G);
	return 0;
}
