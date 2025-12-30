#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct stack_header stack;
struct stack_header {
	elem value;
	stack *next;
};

bool stack_empty(stack *S) {
	return (S->next == NULL);
}

stack* stack_new(void) {
	stack *S = malloc(sizeof *S);
	S->value = 0;
	S->next = NULL;
	return S;
}

void push(stack* S, elem v) {
	stack *node= malloc(sizeof *node);
	node->value = v;
	node->next = S->next;
	S->next = node;
}

elem pop(stack* S) {
	if (S->next == NULL) {
		fprintf(stderr, "pop(): stack is empty\n");
		free(S);
		exit(EXIT_FAILURE);
	}

	elem r = S->next->value;
	stack *temp = S->next;
	S->next = S->next->next;
	free(temp);
	return r;
}

void stack_free(stack *S) {
	for (stack *p = S->next; p != NULL;) {
		stack *temp = p;
		p = p->next;
		free(temp);
	}
	free(S);
}

