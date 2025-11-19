#ifndef UBA_H
#define UBA_H

typedef struct uba_header uba;
typedef uba* uba_t;

int uba_len(uba_t A)
/*@requires A != NULL; @*/
/*@ensures \result >= 0; @*/ ;

uba_t uba_new(int size)
/*@requires 0 <= size; @*/
/*@ensures \result != NULL; @*/
/*@ensures uba_len(\result) == size; @*/ ;

char *uba_get(uba_t A, int i)
/*@requires A != NULL; @*/
/*@requires 0 <= i && i < uba_len(A); @*/ ;

void uba_set(uba_t A, int i, char *x)
/*@requires A != NULL; @*/
/*@requires 0 <= i && i < uba_len(A); @*/ ;

void uba_add(uba_t A, char *x)
/*@requires A != NULL; @*/ ;

char *uba_rem(uba_t A)
/*@requires A != NULL; @*/
/*@requires 0 < uba_len(A); @*/ ;

// bonus function
void uba_print(uba_t A)
/*@requires A != NULL; @*/ ;

void uba_free(uba_t A);

#endif
