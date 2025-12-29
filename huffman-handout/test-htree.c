/* Huffman coding
 *
 * Main file for testing is_htree
 * 15-122 Principles of Imperative Computation
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "lib/xalloc.h"
#include "lib/contracts.h"

#include "htree.h"

struct htree_node {
  symbol_t value;
  unsigned int frequency;
  htree *left;
  htree *right;
};

bool is_htree(htree *H);
bool is_htree_leaf(htree *H);
bool is_htree_interior(htree *H);

void test_leaf() {
  // Write tests for is_tree_leaf here
	htree *leaf = xmalloc(sizeof(htree));
	leaf->value = 'e';
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->frequency = 1;
	assert(is_htree_leaf(leaf));
	free(leaf);
	printf("is_htree_leaf() good\n");
}

htree *new_htree(symbol_t v, unsigned int f, htree *left, htree *right) {
	htree *r = xmalloc(sizeof(htree));
	r->value = v;
	r->frequency = f;
	r->left = left;
	r->right = right;
	return r;
}

void test_interior() {
	htree *l = new_htree('a', 3, NULL, NULL);
	htree *r = new_htree('b', 6, NULL, NULL);
	htree *H1 = new_htree('d', 4, l, r);
	assert(!is_htree_interior(H1));
	free(H1);

	htree *H2 = new_htree('d', 9, l, r);
	assert(is_htree_interior(H2));
	free(H2);
	free(l);
	free(r);
	printf("is_htree_interior() good\n");
}

int main () {
	test_leaf();
	test_interior();

  printf("Success!\n");
  return 0;
}
