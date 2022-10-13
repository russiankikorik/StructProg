#include "sllstack.h"
#include <assert.h>

int f0() {
    return 0;
}

int f1() {
    return 1;
}

int f2() {
    return 2;
}

int main() {
    Stack stack;
    stack_create(&stack);
    assert(stack_size(&stack) == 0);
    assert(stack_pop(&stack) == NULL);
    stack_push(&stack, f0);
    assert(stack_size(&stack) == 1);
    assert(stack_peek(&stack) == f0);
    stack_push(&stack, f1);
    assert(stack_size(&stack) == 2);
    assert(stack_peek(&stack) == f1);
    int (*f1a)() = stack_pop(&stack);
    assert(stack_size(&stack) == 1);
    assert(stack_peek(&stack) == f0);
    assert(f1a() == 1);
    int (*f0a)() = stack_pop(&stack);
    assert(stack_size(&stack) == 0);
    assert(stack_peek(&stack) == NULL);
    assert(f0a() == 0);
    return 0;
}






