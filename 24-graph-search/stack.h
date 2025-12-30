typedef struct stack_header *stack_t;
typedef unsigned int elem;

stack_t stack_new(void);

bool stack_empty(stack_t S);

void push(stack_t S, elem v);

elem pop(stack_t S);

void stack_free(stack_t S);
