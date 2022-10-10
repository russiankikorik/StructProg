#include "sllist.h"
#include <assert.h>
#include <stdio.h>

typedef struct tArray {
    int size;
    int* arr;
} Array;

Array* create(int size) {
    Array* array = (Array*)malloc(sizeof(Array));
    array->size = size;
    array->arr = (int*)malloc(size * sizeof(int));
    return array;
}

Array* copy(Array* array) {
    Array* copy = create(array->size);
    return copy;
}

void destroy(void* array) {
    free(((Array*)array)->arr);
    free(array);
}

int compare(void* array1, void* array2) {
    Array* a1 = (Array*)array1;
    Array* a2 = (Array*)array2;
    if (a1->size < a2->size) {
        return -1; 
    }
    else if (a1->size > a2->size) {
        return 1;
    }
    else {
        return 0;
    }
}

void func(void* array) {
    Array* a = (Array*)array;
    printf("%d\n", a->size);
}

int predicate(void* array) {
    Array* a = (Array*)array;
    if (a->size == 30) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    /*    
    Array* a1 = create(10);
    Node* list = NULL;
    list = sllist_append(list, a1);
    assert(sllist_length(list) == 1);
    list = sllist_delete_first(list, destroy);
    assert(sllist_length(list) == 0);
    a1 = create(10);
    list = sllist_prepend(list, a1);
    assert(sllist_length(list) == 1);
    list = sllist_delete_last(list, NULL);
    assert(sllist_length(list) == 0);
    list = sllist_append(list, a1);
    Array* a2 = create(20);
    list = sllist_append(list, a2);
    assert(sllist_length(list) == 2);
    list = sllist_delete_first(list, destroy);
    assert(sllist_length(list) == 1);
    assert(sllist_get(list, 0) == a2);
    a1 = create(10);
    list = sllist_prepend(list, a1);
    assert(sllist_length(list) == 2);
    assert(sllist_get(list, 0) == a1);
    assert(sllist_get(list, 1) == a2);
    list = sllist_delete_last(list, NULL);
    assert(sllist_length(list) == 1);
    assert(sllist_get(list, 0) == a1);
    assert(a2->size == 20);
    list = sllist_append(list, a2);
    Array* a3 = create(30);
    list = sllist_append(list, a3);
    assert(sllist_length(list) == 3);
    Array* a4 = create(5);
    sllist_put(list, 1, a4, destroy);
    assert(((Array*)sllist_get(list, 1))->size == 5);
    assert(((Array*)sllist_get(list, 2))->size == 30);
    assert(((Array*)sllist_get(list, 0))->size == 10);
    a2 = create(5);
    assert(sllist_find(list, a2, compare) == 1);
    assert(sllist_find(list, a1, compare) == 0);
    assert(sllist_find(list, a3, compare) == 2);
    */

    /*
    destroy(a2);
    list = sllist_delete_first(list, destroy);
    list = sllist_delete_first(list, destroy);
    list = sllist_delete_first(list, destroy);
    assert(list == NULL);
    */
    /*
    Array* a1 = create(10);
    Array* a2 = create(20);
    Array* a3 = create(30);
    Node* list = NULL;
    list = sllist_append(list, a1);
    list = sllist_append(list, a2);
    list = sllist_append(list, a3);
    
    list = sllist_delete(list, 0, NULL);
    assert(sllist_length(list) == 2);
    assert(((Array*)sllist_get(list, 0))->size == 20);
    list = sllist_delete(list, 1, NULL);
    assert(sllist_length(list) == 1);
    assert(((Array*)sllist_get(list, 0))->size == 20);
    list = sllist_prepend(list, a1);
    assert(sllist_length(list) == 2);
    list = sllist_append(list, a3);
    assert(sllist_length(list) == 3);
    list = sllist_delete(list, 1, NULL);
    assert(sllist_length(list) == 2);
    assert(((Array*)sllist_get(list, 0))->size == 10);
    assert(((Array*)sllist_get(list, 1))->size == 30);
    
    
    //list = sllist_delete(list, 0, destroy);
    //list = sllist_delete(list, 0, destroy);

    //destroy(a1);
    destroy(a2);
    //destroy(a3);
    */
    ///*
    Array* a1 = create(10);
    Array* a2 = create(20);
    Array* a3 = create(30);
    Array* a3a = create(30);
    Array* a4 = create(50);
    Node* list = NULL;
    list = sllist_insert(list, 0, a1);
    list = sllist_insert(list, 1, a3);
    list = sllist_insert(list, 1, a2);
    list = sllist_insert(list, 3, a4);
    list = sllist_insert(list, 3, a3a);

    Node* list_copy = sllist_copy(list, copy);
    Node* node = list;
    Node* copy_node = list_copy;
    for (;node != NULL;) {
        assert(((Array*)(node->data))->size == ((Array*)(copy_node->data))->size);
        node = node->next;
        copy_node = copy_node->next;
    }
    Node* concat = sllist_concat(NULL, list);
    assert(sllist_length(concat) == 5);
    concat = sllist_concat(concat, list_copy);
    assert(sllist_length(concat) == 10);
    concat = sllist_concat(concat, NULL);
    assert(sllist_length(concat) == 10);
    sllist_foreach(concat, func);
    assert(sllist_find_custom(list, predicate) == 2);
    //*/
    /*
    list = sllist_remove_first(list, a1, compare, destroy);
    assert(sllist_length(list) == 4);
    assert(((Array*)sllist_get(list, 0))->size == 20);
    list = sllist_remove_first(list, a4, compare, destroy);
    assert(sllist_length(list) == 3);
    assert(((Array*)sllist_get(list, 2))->size == 30);
    list = sllist_remove_first(list, a3, compare, destroy);
    assert(sllist_length(list) == 2);
    assert(((Array*)sllist_get(list, 1))->size == 30);
    list = sllist_remove_first(list, a3a, compare, destroy);
    list = sllist_remove_first(list, a2, compare, destroy);
    assert(sllist_length(list) == 0);
    */
    /*
    //All next removes are suicidal
    list = sllist_remove_all(list, a3a, compare, destroy);
    assert(sllist_length(list) == 3);
    assert(((Array*)sllist_get(list, 1))->size == 20);
    assert(((Array*)sllist_get(list, 2))->size == 50);
    list = sllist_remove_all(list, a1, compare, destroy);
    assert(sllist_length(list) == 2);
    assert(((Array*)sllist_get(list, 0))->size == 20);
    list = sllist_remove_all(list, a4, compare, destroy);
    assert(sllist_length(list) == 1);
    assert(((Array*)sllist_get(list, 0))->size == 20);
    list = sllist_delete_first(list, destroy);
    */
    sllist_delete_all(list, destroy);
    return 0;
}






