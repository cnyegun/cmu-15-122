/* queue-test.c */
/**************************************************************************/
/* COPYRIGHT Carnegie Mellon University 2023                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/

#include <stdlib.h> // Standard C library: free(), NULL...
#include <stdbool.h> // Standard true, false, and bool type
#include <stdio.h>   // For printf
#include <assert.h>  // For assert()
#include "lib/contracts.h" // Our contracts library
#include "lib/xalloc.h" // Our allocation library
#include "queue.h" // The queue interface

/* * Struct definitions inferred from usage in queue-test.c1.
 * In C, these must be visible to access members like ->next or ->front.
 */
typedef struct list_node list;
struct list_node {
    void* data;
    list* next;
};

struct queue_header {
    list* front;
    list* back;
    size_t size; // 'int' used in test file, though implementation often uses size_t
};

/* * Forward declarations for helper functions used in the tests.
 * These are likely defined in your queue.c. To run these tests,
 * you may need to compile queue.c and queue-test.c together,
 * and ensure these functions are not static (or include queue.c here).
 */
bool is_inclusive_segment(list* start, list* end, size_t size);
bool is_queue(struct queue_header* Q);

// Helper function definitions

void* int_to_voidptr(int n) {
    int* r = xmalloc(sizeof(int));
    *r = n;
    return (void*) r;
}

void test_is_segment() {
    // 1) base case:
    list* head1 = NULL;
    list* tail1 = NULL;
    size_t size1 = 0;

    // @assert becomes assert()
    assert(is_inclusive_segment(head1, tail1, size1));

    // 2) regular case:
    list* head2 = xmalloc(sizeof(list));
    list* body2 = xmalloc(sizeof(list));
    list* tail2 = xmalloc(sizeof(list));
    size_t size2 = 3;

    head2->data = int_to_voidptr(8);
    head2->next = body2;
    body2->data = int_to_voidptr(5);
    body2->next = tail2;
    tail2->data = int_to_voidptr(15);
    tail2->next = NULL;

    assert(is_inclusive_segment(head2, tail2, size2));

		free(head2->data);
		free(body2->data);
		free(tail2->data);
		free(head2);
		free(body2);
		free(tail2);

    // 3) start=end case:
    list* head3 = xmalloc(sizeof(list));
    list* tail3 = head3;
    size_t size3 = 1;

    head3->data = int_to_voidptr(67);
    head3->next = NULL;

    assert(is_inclusive_segment(head3, tail3, size3));
		free(head3->data);
		free(head3);

    // 4) Tail not reachable case:
    list* head4 = xmalloc(sizeof(list));
    list* body4 = xmalloc(sizeof(list));
    list* tail4 = xmalloc(sizeof(list));
    size_t size4 = 3;

    head4->data = int_to_voidptr(3);
    head4->next = body4;
    body4->data = int_to_voidptr(5);
    body4->next = NULL;
    tail4->data = int_to_voidptr(8);
    tail4->next = NULL;

    assert(is_inclusive_segment(head4, tail4, size4) == false);
    printf("is_inclusive_segment() good!\n");

		free(head4->data);
		free(body4->data);
		free(tail4->data);
		free(head4);
		free(body4);
		free(tail4);
}

void test_is_queue() {
    // Copy from is_segment test 2) regular case
    list* head2 = xmalloc(sizeof(list));
    list* body2 = xmalloc(sizeof(list));
    list* tail2 = xmalloc(sizeof(list));
    size_t size2 = 3;

    head2->data = int_to_voidptr(8);
    head2->next = body2;
    body2->data = int_to_voidptr(5);
    body2->next = tail2;
    tail2->data = int_to_voidptr(15);
    tail2->next = NULL;

    struct queue_header* Q = xmalloc(sizeof(struct queue_header));
    Q->front = head2;
    Q->back = tail2;
    Q->size = size2;

    assert(is_queue(Q));
		queue_free(Q, free);
    printf("is_queue() good!\n");
}

void test_queue_new() {
    queue_t Q = queue_new();
    assert(is_queue(Q));
		queue_free(Q, NULL);
    printf("queue_new() good!\n");
}

void test_enq() {
    // Base case:
    queue_t Q_base = queue_new();
    enq(Q_base, int_to_voidptr(67));
    
    // Casting queue_t to struct pointer to check internals
    assert(*(int*)Q_base->back->data == 67);
		queue_free(Q_base, free);

    // Regular case:
    list* head2 = xmalloc(sizeof(list));
    list* body2 = xmalloc(sizeof(list));
    list* tail2 = xmalloc(sizeof(list));
    size_t size2 = 3;

    head2->data = int_to_voidptr(8);
    head2->next = body2;
    body2->data = int_to_voidptr(5);
    body2->next = tail2;
    tail2->data = int_to_voidptr(15);
    tail2->next = NULL;

    struct queue_header* Q = xmalloc(sizeof(struct queue_header));
    Q->front = head2;
    Q->back = tail2;
    Q->size = size2;

    enq(Q, int_to_voidptr(58));
    assert(*(int*)body2->next->data == 15);
    assert(*(int*)body2->next->next->data == 58);
    assert(*(int*)Q->back->data == 58);
		queue_free(Q, free);
    printf("enq() good!\n");
}

void test_deq() {
    // Base case: size = 1
    queue_t Q_base = queue_new();
    enq(Q_base, int_to_voidptr(67));
    assert(*(int*)Q_base->back->data == 67);

    int* result1 = (int*)deq(Q_base);
    assert(*result1 == 67);
    assert(Q_base->front == NULL);
    assert(Q_base->back == NULL);
    assert(Q_base->size == 0);
		free(result1);
		queue_free(Q_base, NULL);

    // Regular case:
    list* head2 = xmalloc(sizeof(list));
    list* body2 = xmalloc(sizeof(list));
    list* tail2 = xmalloc(sizeof(list));
    size_t size2 = 3;

    head2->data = int_to_voidptr(8);
    head2->next = body2;
    body2->data = int_to_voidptr(5);
    body2->next = tail2;
    tail2->data = int_to_voidptr(15);
    tail2->next = NULL;

    struct queue_header* Q = xmalloc(sizeof(struct queue_header));
    Q->front = head2;
    Q->back = tail2;
    Q->size = size2;
    
    int* result2 = (int*)deq(Q);
    assert(*result2 == 8);
    assert(Q->size == 2);
    
    int* result3 = (int*)deq(Q);
    assert(*result3 == 5);
    assert(Q->size == 1);

    int* result4 = (int*)deq(Q);
    assert(*result4 == 15);
    assert(Q->size == 0);
    assert(Q->front == NULL);
    assert(Q->back == NULL);

		free(result2);
		free(result3);
		free(result4);
		queue_free(Q, free);
    printf("deq() good!\n");
}

void test_peek() {
    queue_t Q = queue_new();
    enq(Q, int_to_voidptr(67));
    enq(Q, int_to_voidptr(5));
    enq(Q, int_to_voidptr(8));
    enq(Q, int_to_voidptr(23));

    assert(*(int*) queue_peek(Q, 0) == 67);
    assert(*(int*) queue_peek(Q, 3) == 23);
    assert(*(int*) queue_peek(Q, 2) == 8);
    assert(*(int*) queue_peek(Q, 1) == 5);
		queue_free(Q, free);
    printf("peek() good!\n");
}

void test_reverse() {
    queue_t Q = queue_new();
    enq(Q, int_to_voidptr(67));
    enq(Q, int_to_voidptr(5));
    enq(Q, int_to_voidptr(8));
    enq(Q, int_to_voidptr(23));
    
    queue_reverse(Q);
    
    assert(*(int*) queue_peek(Q, 0) == 23);
    assert(*(int*) queue_peek(Q, 1) == 8);
    assert(*(int*) queue_peek(Q, 2) == 5);
    assert(*(int*) queue_peek(Q, 3) == 67);
    printf("reverse() good!\n");
		queue_free(Q, &free);
}

int main() {
    // Create a few queues

    // Using them, test the functions you wrote
    test_is_segment();
    test_is_queue();
    test_queue_new();
    test_enq();
    test_deq();
    test_peek();
    test_reverse();

    printf("All tests passed!\n");
    return 0;
}
