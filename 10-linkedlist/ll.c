typedef int elem;
typedef struct list_node list;

struct list_node {
    elem data;
    struct list_node* next;
};


bool rec_is_segment(list* start, list* end) {
    if (start == NULL) return false;
    if (start == end) return true;

    return is_segment(start->next, end);
}

bool while_is_segment(list* start, list* end) {
    list* l = start;

    while (l != NULL) {
        if (l == end) return true;
        l = l->next;
    } 

    return false;
}

bool for_is_segment(list* start, list* end) {
    for (list* l = start; l != NULL; l = l->next) {
        if (l == end) return true;
    }

    return false;
}

bool is_acyclic(list* start) {
    if (start == NULL) return true;

    list* h = start;
    list* t = start->next;

    while (h != t) {
        if (h == NULL || h->next == NULL)
            return true;
        h = h->next->next;
        t = t->next;
    }

    return false;
}

typedef struct queue_header queue;
struct queue_header {
    list* front;
    list* back;
};

bool is_queue(queue* Q) {
    return Q != NULL 
        && is_acyclic(Q->front);
        && is_segment(Q->front, Q->back);
}

bool queue_empty(queue* Q) {
    return Q->front == Q->back;
}

queue* queue_new()
//@ensures is_queue(\result);
//@ensures queue_empty(\result);
{
    queue* Q = alloc(queue);
    list *dummy = alloc(list);
    Q->front = dummy;
    Q->back = dummy;
    return Q;
}

void enq(queue* Q, elem x)
//@requires is_queue(Q);
//@ensures is_queue(Q);
{
    list* new_dummy = alloc(list);
    back->data = x;
    back->next = new_dummy;
    back = new_dummy;
}

void deq(queue* Q)
//@requires is_queue(Q);
//@requires !queue_empty(Q);
//@ensures is_queue(Q);
{
    elem x = Q->front->data;
    front = Q->front->next;
    return x;
}

typedef stack* stack_t;

typedef struct stack_header stack;
struct stack_header {
    list* top;
    list* floor;
}

bool is_stack(stack* S) {
    return S != NULL
        && is_acyclic(S->top, S->floor)
        && is_segment(S->top, S->floor);
}

bool stack_empty(stack* S) {
    return S->top == S->floor;
}

elem pop(stack* S)
//@requires is_stack(S);
//@requires !stack_empty(S);
//@ensures is_stack(S);
{
    elem x = S->top->data;
    S->top = S->top->next;
    return x;
}

void push(stack* S, elem x)
//@requires is_stack(S);
//@ensures is_stack(S);
{
    list* new_node = alloc(list);
    new_node->data = x;
    new_node->next = S->top;
    S->top = new_node;
}

typedef stack* stack_t;

