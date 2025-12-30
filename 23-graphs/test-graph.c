#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "graph.h"

void test_graph_creation() {
    printf("Testing graph creation...\n");
    
    graph_t G = graph_new(5);
    assert(G != NULL);
    assert(graph_size(G) == 5);
    
    // Verify no edges initially
    for (unsigned int i = 0; i < 5; i++) {
        for (unsigned int j = 0; j < 5; j++) {
            assert(!graph_hasedge(G, i, j));
        }
    }
    
    graph_free(G);
    printf("\u2713 Graph creation tests passed\n");
}

void test_edge_operations() {
    printf("Testing edge operations...\n");
    
    graph_t G = graph_new(4);
    
    // Add some edges
    graph_addedge(G, 0, 1);
    assert(graph_hasedge(G, 0, 1));
    assert(graph_hasedge(G, 1, 0)); // Undirected
    
    graph_addedge(G, 0, 2);
    assert(graph_hasedge(G, 0, 2));
    assert(graph_hasedge(G, 2, 0));
    
    graph_addedge(G, 1, 3);
    assert(graph_hasedge(G, 1, 3));
    assert(graph_hasedge(G, 3, 1));
    
    // Check non-existent edges
    assert(!graph_hasedge(G, 0, 3));
    assert(!graph_hasedge(G, 1, 2));
    assert(!graph_hasedge(G, 2, 3));
    
    // Verify no self-edges
    for (unsigned int i = 0; i < 4; i++) {
        assert(!graph_hasedge(G, i, i));
    }
    
    graph_free(G);
    printf("\u2713 Edge operation tests passed\n");
}

void test_neighbors_empty() {
    printf("Testing neighbors on isolated vertex...\n");
    
    graph_t G = graph_new(5);
    
    // Vertex with no neighbors
    neighbors_t nbors = graph_get_neighbors(G, 0);
    assert(nbors != NULL);
    assert(!graph_hasmore_neighbors(nbors));
    graph_free_neighbors(nbors);
    
    graph_free(G);
    printf("\u2713 Empty neighbors test passed\n");
}

void test_neighbors_single() {
    printf("Testing single neighbor...\n");
    
    graph_t G = graph_new(3);
    graph_addedge(G, 0, 1);
    
    neighbors_t nbors = graph_get_neighbors(G, 0);
    assert(graph_hasmore_neighbors(nbors));
    
    vertex neighbor = graph_next_neighbor(nbors);
    assert(neighbor == 1);
    
    assert(!graph_hasmore_neighbors(nbors));
    
    graph_free_neighbors(nbors);
    graph_free(G);
    printf("\u2713 Single neighbor test passed\n");
}

void test_neighbors_multiple() {
    printf("Testing multiple neighbors...\n");
    
    graph_t G = graph_new(5);
    graph_addedge(G, 0, 1);
    graph_addedge(G, 0, 2);
    graph_addedge(G, 0, 4);
    
    neighbors_t nbors = graph_get_neighbors(G, 0);
    
    // Should have 3 neighbors: 1, 2, 4
    assert(graph_hasmore_neighbors(nbors));
    vertex n1 = graph_next_neighbor(nbors);
    assert(n1 == 1);
    
    assert(graph_hasmore_neighbors(nbors));
    vertex n2 = graph_next_neighbor(nbors);
    assert(n2 == 2);
    
    assert(graph_hasmore_neighbors(nbors));
    vertex n3 = graph_next_neighbor(nbors);
    assert(n3 == 4);
    
    assert(!graph_hasmore_neighbors(nbors));
    
    graph_free_neighbors(nbors);
    graph_free(G);
    printf("\u2713 Multiple neighbors test passed\n");
}

void test_neighbors_all_connected() {
    printf("Testing vertex connected to all others...\n");
    
    graph_t G = graph_new(4);
    graph_addedge(G, 0, 1);
    graph_addedge(G, 0, 2);
    graph_addedge(G, 0, 3);
    
    neighbors_t nbors = graph_get_neighbors(G, 0);
    
    int count = 0;
    while (graph_hasmore_neighbors(nbors)) {
        vertex v = graph_next_neighbor(nbors);
        assert(v >= 1 && v <= 3);
        count++;
    }
    assert(count == 3);
    
    graph_free_neighbors(nbors);
    graph_free(G);
    printf("\u2713 All connected test passed\n");
}

void test_neighbors_symmetric() {
    printf("Testing symmetric neighbor relations...\n");
    
    graph_t G = graph_new(3);
    graph_addedge(G, 0, 1);
    graph_addedge(G, 1, 2);
    
    // Check neighbors of 0
    neighbors_t nbors0 = graph_get_neighbors(G, 0);
    assert(graph_hasmore_neighbors(nbors0));
    assert(graph_next_neighbor(nbors0) == 1);
    assert(!graph_hasmore_neighbors(nbors0));
    graph_free_neighbors(nbors0);
    
    // Check neighbors of 1 (should have 0 and 2)
    neighbors_t nbors1 = graph_get_neighbors(G, 1);
    assert(graph_hasmore_neighbors(nbors1));
    assert(graph_next_neighbor(nbors1) == 0);
    assert(graph_hasmore_neighbors(nbors1));
    assert(graph_next_neighbor(nbors1) == 2);
    assert(!graph_hasmore_neighbors(nbors1));
    graph_free_neighbors(nbors1);
    
    // Check neighbors of 2
    neighbors_t nbors2 = graph_get_neighbors(G, 2);
    assert(graph_hasmore_neighbors(nbors2));
    assert(graph_next_neighbor(nbors2) == 1);
    assert(!graph_hasmore_neighbors(nbors2));
    graph_free_neighbors(nbors2);
    
    graph_free(G);
    printf("\u2713 Symmetric neighbor test passed\n");
}

void test_complete_graph() {
    printf("Testing complete graph...\n");
    
    graph_t G = graph_new(4);
    
    // Create complete graph (all vertices connected)
    for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = i + 1; j < 4; j++) {
            graph_addedge(G, i, j);
        }
    }
    
    // Each vertex should have 3 neighbors
    for (unsigned int v = 0; v < 4; v++) {
        neighbors_t nbors = graph_get_neighbors(G, v);
        int count = 0;
        while (graph_hasmore_neighbors(nbors)) {
            graph_next_neighbor(nbors);
            count++;
        }
        assert(count == 3);
        graph_free_neighbors(nbors);
    }
    
    graph_free(G);
    printf("\u2713 Complete graph test passed\n");
}

void test_star_graph() {
    printf("Testing star graph (one center, all others connected to it)...\n");
    
    graph_t G = graph_new(6);
    
    // Vertex 0 is center, connected to all others
    for (unsigned int i = 1; i < 6; i++) {
        graph_addedge(G, 0, i);
    }
    
    // Center should have 5 neighbors
    neighbors_t nbors_center = graph_get_neighbors(G, 0);
    int count = 0;
    while (graph_hasmore_neighbors(nbors_center)) {
        graph_next_neighbor(nbors_center);
        count++;
    }
    assert(count == 5);
    graph_free_neighbors(nbors_center);
    
    // Each outer vertex should have exactly 1 neighbor (the center)
    for (unsigned int v = 1; v < 6; v++) {
        neighbors_t nbors = graph_get_neighbors(G, v);
        assert(graph_hasmore_neighbors(nbors));
        vertex neighbor = graph_next_neighbor(nbors);
        assert(neighbor == 0);
        assert(!graph_hasmore_neighbors(nbors));
        graph_free_neighbors(nbors);
    }
    
    graph_free(G);
    printf("\u2713 Star graph test passed\n");
}

int main() {
    printf("Running graph tests...\n\n");
    
    test_graph_creation();
    test_edge_operations();
    test_neighbors_empty();
    test_neighbors_single();
    test_neighbors_multiple();
    test_neighbors_all_connected();
    test_neighbors_symmetric();
    test_complete_graph();
    test_star_graph();
    
    printf("\n\u2713\u2713\u2713 ALL TESTS PASSED \u2713\u2713\u2713\n");
    return 0;
}
