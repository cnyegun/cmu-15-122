typedef struct queue_header *queue_t;
typedef unsigned int elem;

queue_t queue_new(void);

bool queue_empty(queue_t Q);

void enq(queue_t Q, elem v);

elem deq(queue_t Q);

void queue_free(queue_t Q);
