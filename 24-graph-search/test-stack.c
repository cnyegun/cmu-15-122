#include "stack.h"
#include <assert.h>
#include <stdio.h>

int main() {
	stack_t S = stack_new();
	push(S, 1);
	push(S, 2);
	push(S, 3);
	push(S, 4);
	push(S, 5);

	for (int i = 0; i < 5; i++) {
		printf("%zu\n", pop(S));
	}

	stack_free(S);

	return 0;
}
