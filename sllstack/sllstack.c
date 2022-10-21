#include "../sllist/sllist.h"
#include "sllstack.h"
#include <stdlib.h>

void stack_create(Stack* pstack) {
    Stack stack;
    SLLnode* list = NULL;
    stack.top = list;
    *pstack = stack;
}

void stack_destroy(Stack* pstack) {
    sllist_delete_all(pstack->top, NULL);
}

void stack_push(Stack* pstack, void* value) {
    pstack->top = sllist_prepend(pstack->top, value);
}

int stack_size(Stack* pstack) {
    return sllist_length(pstack->top);
}

void* stack_pop(Stack* pstack) {
    void* value = sllist_get(pstack->top, 0);
    pstack->top = sllist_delete_first(pstack->top, NULL);
    return value;
}

void* stack_peek(Stack* pstack) {
    return sllist_get(pstack->top, 0);
}
