#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DEFAULT_LIMIT 1
#define RESIZE_FACTOR 2

struct uba_header {
	int size;
	int limit;
	int* data;
};

typedef struct uba_header uba;

int uba_len(uba* A) {
	return A->size;
}

bool is_uba_empty(uba* A) {
	return A->size == 0;
}

uba* uba_new() {
	uba* A = (uba*)malloc(sizeof(uba*));
	A->size = 0;
	A->limit = DEFAULT_LIMIT;
	A->data = (int*)malloc(sizeof(int) * DEFAULT_LIMIT);
	return A;
}

void uba_display(uba* A) {
	printf("\nAddress: %p\nSize: %d\nLimit: %d\n", A, A->size, A->limit);
	if (is_uba_empty(A)) {
		printf("The array is empty.\n");
		return;
	}
	for (int i = 0; i < A->size; i++) {
		printf("[%d] ", A->data[i]);
	}
	printf("\n");
}

int uba_get(uba* A, int i) {
	return A->data[i];
}

void uba_set(uba* A, int i, int x) {
	A->data[i] = x;
}

void uba_upsize(uba* A) {
	int new_limit = A->limit * RESIZE_FACTOR;
	A->limit = new_limit;
	int* B = (int*)malloc(sizeof(int) * new_limit);
	for (int i = 0; i < A->size; i++) {
		B[i] = A->data[i];
	}
	free(A->data);
	A->data = B;
}

void uba_add(uba* A, int x) {
	A->data[A->size] = x;
	A->size++;
	if (A->size == A->limit) {
		uba_upsize(A);
	}
}

int main() {
	uba* A = uba_new();

	for (int i = 0; i < 99999; i++) {
		uba_add(A, i / 1000);
	}

	printf("\nDone!\n");
	return 0;
}
