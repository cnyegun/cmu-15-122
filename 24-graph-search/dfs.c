#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "contracts.h"
#include "stack.h"

// size of *mark array: graph_size(G);

bool dfs_helper(graph_t G, bool *mark, vertex start, vertex target) {
	REQUIRES(G != NULL && mark != NULL);
	REQUIRES(start < graph_size(G) && target < graph_size(G));
	REQUIRES(!mark[start]);

	// Base case: start == target
	if (start == target) return true;

	// Recursive case:
	// Create a list of neighbors from current vertex
	neighbors_t nbors = graph_get_neighbors(G, start);
	while (graph_hasmore_neighbors(nbors)) {
		vertex v = graph_next_neighbor(nbors);
		if (!mark[v]) {
			mark[v] = true;
			bool try = dfs_helper(G, mark, v, target);
			if (try) {
				graph_free_neighbors(nbors);
				return true;
			}
		}
	}

	graph_free_neighbors(nbors);
	return false;
}

bool dfs_recursive(graph_t G, vertex start, vertex target) {
	REQUIRES(G != NULL);
	REQUIRES(start < graph_size(G) && target < graph_size(G));

	// Simple case: 
	if (start == target) return true;

	// Create a array to check visited vertex
	bool *mark = calloc(graph_size(G), sizeof *mark);
	mark[start] = true;

	bool result = dfs_helper(G, mark, start, target);
	free(mark);
	return result;
}

bool dfs_worklist(graph_t G, vertex start, vertex target) {
	REQUIRES (G != NULL);
	REQUIRES(start < graph_size(G) && target < graph_size(G));

	// Special case: start == target
	if (start == target) return true;	
		
	// We need a array to check visited vertex
	bool *mark = calloc(graph_size(G), sizeof *mark);
	// We are in the start node
	mark[start] = true;

	// Create a worklist 
	stack_t worklist = stack_new();	
	// Init with our starting vertex
	push(worklist, start);
	
	// Do this until nothing left in the worklist 
	while (!stack_empty(worklist)) {
		vertex v = pop(worklist);
		if (v == target) {
			stack_free(worklist);
			free(mark);
			return true;
		}

		// * This is not the target we are looking for
		// Append all the unknown neighbors of this node
		neighbors_t nbors = graph_get_neighbors(G, v);
		while (graph_hasmore_neighbors(nbors)) {
			vertex w = graph_next_neighbor(nbors);
			if (!mark[w]) {
				push(worklist, w);
				mark[w] = true;
			}
		}
		graph_free_neighbors(nbors);
	}

	// There is no path
	free(mark);
	stack_free(worklist);
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

	assert(dfs_recursive(G, 3, 2));
	assert(dfs_recursive(G, 1, 3));
	assert(!dfs_recursive(G, 0, 6));
	printf("All tests passed!\n");
	graph_free(G);
	return 0;
}
