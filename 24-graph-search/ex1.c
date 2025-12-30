#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "contracts.h"
#include "queue.h"

// size of *mark array: graph_size(G);

char edge_name[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

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
		printf("%c ", edge_name[v]);
		if (v == target) {
			queue_free(worklist);
			free(mark);
			printf("\n\n");
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
	printf("\n\n");
	return false;
}

int main() {
	graph_t G = graph_new(7);
	// A = 0; B = 1; C = 2; D = 3; E = 4; F = 5; G = 6
	graph_addedge(G, 0, 1); // A-B
	graph_addedge(G, 0, 2); // A-C

	graph_addedge(G, 1, 3); // B-D
	graph_addedge(G, 1, 4); // B-E

	graph_addedge(G, 2, 5); // C-F

	graph_addedge(G, 3, 4); // D-E
	graph_addedge(G, 3, 5); // D-F
	graph_addedge(G, 3, 6); // D-G

	graph_addedge(G, 4, 6); // E-G

	graph_addedge(G, 5, 6); // F-G


	printf("Path from [%c] to [%c]:\n", edge_name[3], edge_name[2]); 
	assert(bfs(G, 3, 2));
	printf("Path from [%c] to [%c]:\n", edge_name[1], edge_name[3]); 
	assert(bfs(G, 1, 3));
	printf("All tests passed!\n");
	graph_free(G);
	return 0;
}
