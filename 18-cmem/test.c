#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uba.h"

int main() {
	uba_t A = uba_new(0);
	for (int i = 0; i < 109; i++) {
		uba_add(A, "Helloooo");
	}

	for (int i = 0; i < 15; i++) {
		uba_rem(A);
	}
	uba_print(A);
	printf("len: %d\n", uba_len(A));
	uba_free(A);
	return 0;
}
