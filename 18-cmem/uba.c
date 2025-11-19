#include "uba.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct uba_header {
	int size;		// 0 <= size && size < limit
	int limit;		// 0 < limit
	char **data;	// strlen(data) == limit
};

int uba_len(uba* A) {
	return A->size;
}

char *uba_get(uba *A, int i) {
	if (0 <= i && i < uba_len(A)) {
		return A->data[i];
	}
	return NULL;
}

uba *uba_new(int size)
{
	if (size < 0) return NULL;
	uba *A = malloc(sizeof *A);
	int limit = size == 0 ? 1 : size * 2;
	A->data = malloc(sizeof *A->data * limit);
	A->size = size;
	A->limit = limit;
	return A;
}

void uba_resize(uba* A, int new_limit)
{
	if (A == NULL) return;
	if (new_limit <= 0) return;
	if (new_limit == A->limit) return;
	if (A->size > new_limit) return;
	char **B = malloc(sizeof *B * new_limit);

	for (int i = 0; i < A->size; i++) {
		B[i] = A->data[i];
	}
	A->limit = new_limit;
	free(A->data);
	A->data = B;
}

void uba_add(uba* A, char* s) {
	A->data[A->size] = s;
	(A->size)++;

	if (A->size < A->limit) return;
	uba_resize(A, A->limit * 2);
}

char *uba_rem(uba* A) {
	if (A->size <= 0) return NULL;

	(A->size)--;
	char *x = A->data[A->size];
	
	if (A->limit >= 4 && A->size <= A->limit / 4)
		uba_resize(A, A->limit / 2);
	
	return x;
}

void uba_print(uba* A) {
	printf("[");
	for (int i = 0; i < A->size; i++) {
		printf("%s", A->data[i]);
		if (i+1 != A->size) printf(", ");
	}
	printf("]\n");
}

void uba_free(uba* A) {
	if (A == NULL) return;
	free(A->data);
	free(A);
	return;
}
