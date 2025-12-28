/* Packing and unpacking ASCII bits into bytes
 *
 * 15-122 Principles of Imperative Computation
 */

#include <stdint.h>

#include "encode.h"

#ifndef BITPACKING_H
#define BITPACKING_H

// Returns ceil(bits_len/8)
unsigned int num_padded_bytes(unsigned int bit_len);

// Pack a NUL-terminated string of ASCII bits into an array of bytes; length = ceil(strlen(bits)/8)
uint8_t* pack(bit_t *bits);

// Unpack an array of bytes c of length len into a NUL-terminated string of ASCII bits
bit_t* unpack(uint8_t *c, size_t len);

#endif /* BITPACKING_H */
