#include "../sllist/sllist.h"

#ifndef _SLLSTACK_
#define _SLLSTACK_

typedef struct tStack {
    Node* top;
} Stack;

void stack_create(Stack* pstack);

void stack_destroy(Stack* pstack);

void stack_push(Stack* pstack, void* value);

int stack_size(Stack* pstack);

void* stack_pop(Stack* pstack);

void* stack_peek(Stack* pstack);

#endif

