#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct list_node node;
struct list_node {
	elem value;
	node *next;
};

typedef struct queue_header queue;
struct queue_header {
	node* front;
	node* back;
};

bool queue_empty(queue *Q) {
	return (Q->front == NULL);
}

queue* queue_new(void) {
	queue *Q = malloc(sizeof *Q);
	Q->front = NULL;
	Q->back = NULL;
	return Q;
}

void enq(queue* Q, elem v) {
	node *item = malloc(sizeof *item);
	item->value = v;
	item->next = NULL;

	if (queue_empty(Q)) {
		Q->front = item;
		Q->back = item;
	} else {
		Q->back->next = item;
		Q->back = item;
	}
}

elem deq(queue* Q) {
	if (queue_empty(Q)) {
		fprintf(stderr, "pop(): queue is empty\n");
		exit(EXIT_FAILURE);
	}

	elem r = Q->front->value;
	node *tmp = Q->front;
	Q->front = Q->front->next;
	free(tmp);
	return r;
}

void queue_free(queue *Q) {
	for (node *p = Q->front; p != NULL;) {
		node *temp = p;
		p = p->next;
		free(temp);
	}
	free(Q);
}

