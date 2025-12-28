/* Encoding and decoding a file given a frequency table
 *
 * 15-122 Principles of Imperative Computation
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "htree.h"

#ifndef ENCODE_H
#define ENCODE_H


// Set verbose flag
void verbose_huffman();

// Encode source according to codetable
bit_t* encode_src(codetable_t table, symbol_t *src, size_t src_len);
// Decode code according to H, putting decoded length in src_len
symbol_t* decode_src(htree *H, bit_t *code, size_t *src_len);

// Encode source file to code file according to codetable
void encode(codetable_t table, char *src_fname, char *code_fname);
// Decode code file to source file according to H
void decode(htree *H, char *src_fname, char *code_fname, codetable_t table);

#endif /* ENCODE_H */
