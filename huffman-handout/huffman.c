/* Huffman coding
 *
 * 15-122 Principles of Imperative Computation
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "lib/contracts.h"
#include "lib/xalloc.h"
#include "lib/file_io.h"
#include "lib/pq.h"

#include "freqtable.h"
#include "htree.h"
#include "encode.h"
#include "bitpacking.h"

// Print error message
void error(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

/* in htree.h: */
/* typedef struct htree_node htree; */
struct htree_node {
  symbol_t value;
  unsigned int frequency;
  htree *left;
  htree *right;
};

/**********************************************/
/* Task 1: Checking data structure invariants */
/**********************************************/

/* forward declaration -- DO NOT MODIFY */
bool is_htree(htree *H);

bool is_htree_leaf(htree *H) {
	return H != NULL
			&& H->frequency > 0 
			&& H->left == NULL 
			&& H->right == NULL;
}

bool is_htree_interior(htree *H) {
	return H != NULL
			&& H->left != NULL && H->right != NULL
			&& is_htree(H->left) && is_htree(H->right)
			&& H->left->frequency + H->right->frequency == H->frequency;
}

bool is_htree(htree *H) {
	return H != NULL
			&& (is_htree_leaf(H) || is_htree_interior(H));
}


/********************************************************/
/* Task 2: Building Huffman trees from frequency tables */
/********************************************************/

/* for lib/pq.c */
bool htree_higher_priority(elem e1, elem e2) {
	htree *h1 = (htree*) e1;
	htree *h2 = (htree*) e2;
	return h1->frequency < h2->frequency;
}

htree* new_htree(
	symbol_t value, 
	unsigned int frequency, 
	htree* left, 
	htree* right
) {
	htree *r = xmalloc(sizeof(htree));
	r->value = value;
	r->frequency = frequency;
	r->left = left;
	r->right = right;
	return r;
}

// build a htree from a frequency table
htree* build_htree(freqtable_t table) {
	// If less than 2 non-zero value in the table -> error
	int count = 0;
	for (int i = 0; i < NUM_SYMBOLS; i++) {
		if (table[i] > 0) count++;
		if (count >= 2) break;
	}
	if (count < 2) error("Need at least 2 symbols with non-zero freqency");

	// Create all the leaves from the freqtable and add to the queue
	pq_t Q = pq_new(NUM_SYMBOLS, htree_higher_priority, free);
	for (int i = 0; i < NUM_SYMBOLS; i++) {
		if (table[i] > 0) 
			pq_add(Q, (void*) new_htree(i, table[i], NULL, NULL));
	}

	while (!pq_empty(Q)) {
		htree *H1 = (htree*) pq_rem(Q);
		if (pq_empty(Q)) {
			pq_free(Q);
			return H1;
		}
		htree *H2 = (htree*) pq_rem(Q);
		htree *I = new_htree('\0', H1->frequency + H2->frequency, H1, H2);
		pq_add(Q, (void*) I);
	}
	// Shouldn't reach here...
  return NULL;
}

/*******************************************/
/*  Task 3: decoding a text                */
/*******************************************/

// Decode code according to H, putting decoded length in src_len
symbol_t* decode_src(htree *H, bit_t *code, size_t *src_len) {
	htree *p = H;
	// Count how many symbols
	size_t count = 0;
	for (int i = 0; code[i] != '\0'; i++) {
		if (code[i] == '0')
			p = p->left;
		else {
			p = p->right;
		}
		if (is_htree_leaf(p)) {
			count++;
			p = H;
		}
	}
	*src_len = count;
	symbol_t *r = xcalloc(count, sizeof(symbol_t));

	p = H;
	int index = 0;
	for (int i = 0; code[i] != '\0'; i++) {
		if (code[i] == '0') {
			p = p->left;
		} else {
			p = p->right;
		}
		if (is_htree_leaf(p)) {
			r[index] = p->value;
			index++;
			p = H;
		}
	}
	return r;
}


/***************************************************/
/* Task 4: Building code tables from Huffman trees */
/***************************************************/

codetable_t htree_to_codetable(htree *H);
void _htree_to_codetable_helper(htree *H, bitstring_t rsf, codetable_t table) {
	if (is_htree_leaf(H)) {
		table[H->value] = rsf;
		return;
	} 
	bitstring_t rsf_left;
	bitstring_t rsf_right;
	// Go left!
	// Make a copy of current position
	if (rsf != NULL) {
		rsf_left = malloc(strlen(rsf) + 2);
		strcpy(rsf_left, rsf);
	}
	else {
		rsf_left = malloc(2);
		rsf_left[0] = '\0';
	}
	strcat(rsf_left, "0");
	_htree_to_codetable_helper(H->left, rsf_left, table);

	// Go right!
	// Make a copy of current position
	if (rsf != NULL) {
		rsf_right = malloc(strlen(rsf) + 2);
		strcpy(rsf_right, rsf);
	}
	else {
		rsf_right = malloc(2);
		rsf_right[0] = '\0';
	}
	strcat(rsf_right, "1");
	_htree_to_codetable_helper(H->right, rsf_right, table);

	free(rsf);
	return;
}

// Returns code table for characters in H
codetable_t htree_to_codetable(htree *H) {
	codetable_t table = xcalloc(NUM_SYMBOLS, sizeof(bitstring_t));
	bitstring_t init = NULL;

	_htree_to_codetable_helper(H, init, table);
	return table;
}

/*******************************************/
/*  Task 5: Encoding a text                */
/*******************************************/

// Encodes source according to codetable
bit_t* encode_src(codetable_t table, symbol_t *src, size_t src_len) {
	// First pass to determine the length of the return array
	size_t size = 0;
	for (size_t i = 0; i < src_len; i++) {
		size += strlen(table[src[i]]);
	}
	bit_t* r = malloc(sizeof(bit_t) * size + 1);
	r[0] = '\0';
	for (size_t i = 0; i < src_len; i++) {
		strcat(r, table[src[i]]);
	}
	return r;
}


/**************************************************/
/*  Task 6: Building a frequency table from file  */
/**************************************************/

// Build a frequency table from a source file (or STDIN)
freqtable_t build_freqtable(char *fname) {
  // WRITE ME
  (void)fname; // bogus
  return NULL; // bogus
}



/************************************************/
/*  Task 7: Packing and unpacking a bitstring   */
/************************************************/

// Pack a string of bits into an array of bytes
uint8_t* pack(bit_t *bits) {
  // WRITE ME
  (void)bits;  // bogus
  return NULL; // bogus
}

// Unpack an array of bytes c of length len into a NUL-terminated string of ASCII bits
bit_t* unpack(uint8_t *c, size_t len) {
  // WRITE ME
  (void)c; (void)len;  // bogus
  return NULL;         // bogus
}
