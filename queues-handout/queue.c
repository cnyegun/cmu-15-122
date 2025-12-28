#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lib/contracts.h"
#include "lib/xalloc.h"
#include "queue.h"

/************************************************************************/
/**************************** Client Interface **************************/

typedef void print_data_fn(void* x);            // may be useful for debugging
typedef bool check_property_fn(void* x);
typedef void* iterate_fn(void* accum, void* x);

/************************* End Client Interface *************************/
/************************************************************************/

/************************************************************************/
/************************* BEGIN IMPLEMENTATION *************************/

typedef struct list_node list;
struct list_node {
  void* data; // Could be NULL
  list* next;
};

typedef struct queue_header queue;
struct queue_header {
  list* front;
  list* back;
  size_t size;
};

bool is_inclusive_segment(list* start, list* end, int i) {
	// Base case: empty segment
	if (start == NULL) 
		return i == 0; 
	// Size = 1
	if (start == end) 
		return (start->next == NULL && i == 1);
	// Recursive case
	return is_inclusive_segment(start->next, end, i - 1);
}

bool is_queue(queue* Q) {
  return Q != NULL
			&& is_inclusive_segment(Q->front, Q->back, Q->size);
}

// Returns a empty queue
queue* queue_new() {
ENSURES( is_queue(\result) );
	queue* Q = xmalloc(sizeof(queue));
	Q->front = NULL;
	Q->back = NULL;
	Q->size = 0;
	return Q;
}

size_t queue_size(queue* Q) {
REQUIRES( is_queue(Q) );
ENSURES( \result >= 0 );
	return Q->size;
}

// add an item to the back of the queue O(1)
void enq(queue* Q, void* x) {
REQUIRES( is_queue(Q) );
ENSURES( is_queue(Q) );
	// Base case: Q is empty ---> front = back = x and Q->size = 1;
	if (Q->front == NULL) {
		Q->front = xmalloc(sizeof(list));
		Q->front->data = x;
		Q->front->next = NULL;
		Q->back = Q->front;
		Q->size++;
		return;
	}
	// Regular case: create a new list_node
	// 							 point the tail->next to this new node
	// 							 point the tail to this new node
	list* new_node = xmalloc(sizeof(list));
	new_node->data = x;
	new_node->next = NULL;
	Q->back->next = new_node;
	Q->back = new_node;
	Q->size++;
}

void* deq(queue* Q) {
REQUIRES( is_queue(Q) && queue_size(Q) > 0 );
ENSURES( is_queue(Q) );
	// Base case: size = 1
	if (Q->size == 1) {
		void* result = Q->front->data;
		free(Q->front);
		Q->front = NULL;
		Q->back = NULL;
		Q->size = 0;
		return result;
	}
	void* result = Q->front->data;
	list* temp = Q->front;
	Q->front = Q->front->next;
	free(temp);
	Q->size--;
	return result;
}

void* queue_peek(queue* Q, size_t i) {
REQUIRES( is_queue(Q) && 0 <= i && i < queue_size(Q) );
ENSURES( is_queue(Q) );
	list* p = Q->front;
	for (int j = 0; j < i; j++) {
		p = p->next;
	}
	return p->data;
}

void queue_reverse(queue* Q) {
REQUIRES( is_queue(Q) );
ENSURES( is_queue(Q) );
	list* prev = NULL;
	list* foll = NULL;

	for (list* curr = Q->front; curr != NULL; curr = foll) {
		foll = curr->next;
		curr->next = prev;
		prev = curr;
	}

	Q->back = Q->front;
	Q->front = prev;
}

/* O(n) worst case; assuming P is O(1) */
bool queue_all(queue* Q, check_property_fn* P) {
REQUIRES( is_queue(Q) && P != NULL );
	for (list* p = Q->front; p != NULL; p = p->next) {
		if (!(*P)(p->data))
			return false;
	}
	return true;
}

void* queue_iterate(queue* Q, void* base, iterate_fn* F) {
REQUIRES( is_queue(Q) && F != NULL );
	void* acc = base;
	for (list* p = Q->front; p != NULL; p = p->next) {
		acc = (*F)(acc, p->data);
	}
	return acc;
}

void queue_free(queue* Q, free_fn *F) {
REQUIRES( Q != NULL );
	if (F == NULL) {
		for (list* p = Q->front; p != NULL;) {
			list* temp = p;
			p = p->next;
			free(temp);
		}
		free(Q);
		return;
	};
	ASSERT( F != NULL );
	for (list* p = Q->front; p != NULL;) {
		list* temp = p;
		(*F)(p->data);
		p = p->next;
		free(temp);
	}
	free(Q);
	return;
}
