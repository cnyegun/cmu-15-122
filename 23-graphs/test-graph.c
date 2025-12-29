#include "graph.h"

int main() {
	graph_t G = graph_new(5);

	graph_addedge(G, 0, 1);
	graph_addedge(G, 1, 2);
	graph_addedge(G, 2, 3);
	graph_addedge(G, 0, 4);
	graph_addedge(G, 1, 4);
	graph_addedge(G, 2, 4);

	/* A B C D E
	A [0 1 0 0 1]	
	B [1 0 1 0 1]
	C [0 1 0 1 1]
	D [0 0 1 0 0]
	E [1 1 1 0 0]
	*/	
	graph_free(G);
}
