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
    if (a->size == 20) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    //length, prepend, get, delete_all
    {
        Array* a0 = create(0);
        Array* a1 = create(10);
        Array* a2 = create(20);
        Node* list = NULL;
        assert(sllist_length(list) == 0);
        list = sllist_prepend(list, a0);
        assert(sllist_length(list) == 1);
        assert(sllist_get(list, 0) == a0);
        list = sllist_prepend(list, a1);
        assert(sllist_length(list) == 2);
        assert(sllist_get(list, 0) == a1);
        assert(sllist_get(list, 1) == a0);
        list = sllist_prepend(list, a2);
        assert(sllist_length(list) == 3);
        assert(sllist_get(list, 0) == a2);
        assert(sllist_get(list, 1) == a1);
        assert(sllist_get(list, 2) == a0);
        assert(sllist_get(list, 10) == NULL);
        sllist_delete_all(list, destroy);
    }
    //append, delete_first, delete_last
    {
        Array* a0 = create(0);
        Array* a1 = create(10);
        Array* a2 = create(20);
        Array* a3 = create(30);
        Array* a4 = create(40);
        Array* a5 = create(50);
        Node* list = NULL;
        list = sllist_append(list, a0);
        assert(sllist_length(list) == 1);
        assert(sllist_get(list, 0) == a0);
        list = sllist_append(list, a1);
        assert(sllist_length(list) == 2);
        assert(sllist_get(list, 0) == a0);
        assert(sllist_get(list, 1) == a1);
        list = sllist_append(list, a2);
        assert(sllist_length(list) == 3);
        assert(sllist_get(list, 0) == a0);
        assert(sllist_get(list, 1) == a1);
        assert(sllist_get(list, 2) == a2);

        list = sllist_append(list, a3);
        list = sllist_delete_first(list, destroy);
        assert(sllist_length(list) == 3);
        assert(sllist_get(list, 0) == a1);
        list = sllist_delete_last(list, destroy); 
        assert(sllist_length(list) == 2);
        assert(sllist_get(list, 1) == a2);

        list = sllist_delete_first(list, destroy);
        assert(sllist_length(list) == 1);
        assert(sllist_get(list, 0) == a2);
        list = sllist_delete_first(list, destroy);
        assert(list == NULL);
        
        list = sllist_append(list, a4);
        list = sllist_append(list, a5);
        list = sllist_delete_last(list, destroy);
        assert(sllist_length(list) == 1);
        assert(sllist_get(list, 0) == a4);
        list = sllist_delete_last(list, destroy);
        assert(list == NULL);
    }
    //get_last, put_last
    {
        Array* a0 = create(0);
        Array* a1 = create(10);
        Array* a2 = create(20);
        Array* a0a = create(30);
        Array* a1a = create(40);
        Array* a2a = create(50);
        Node* list = NULL;
        list = sllist_append(list, a0);
        assert(sllist_get_last(list) == a0);
        sllist_put_last(list, a0a, destroy);
        assert(sllist_get_last(list) == a0a);
        list = sllist_append(list, a1);
        assert(sllist_get_last(list) == a1);
        sllist_put_last(list, a1a, destroy);
        assert(sllist_get_last(list) == a1a);
        list = sllist_append(list, a2);
        assert(sllist_get_last(list) == a2);
        sllist_put_last(list, a2a, destroy);
        assert(sllist_get_last(list) == a2a);
        sllist_delete_all(list, destroy);
    }
    //put
    {
        Array* a0 = create(0);
        Array* a1 = create(10);
        Array* a2 = create(20);
        Array* a0a = create(30);
        Array* a1a = create(40);
        Array* a2a = create(50);
        Node* list = NULL;
        list = sllist_append(list, a0);
        list = sllist_append(list, a1);
        list = sllist_append(list, a2);
        sllist_put(list, 0, a0a, destroy);
        assert(sllist_get(list, 0) == a0a);
        sllist_put(list, 1, a1a, destroy);
        assert(sllist_get(list, 1) == a1a);
        sllist_put(list, 2, a2a, destroy);
        assert(sllist_get(list, 2) == a2a);
        sllist_delete_all(list, destroy);
    }
    //insert, delete
    {
        Array* a0 = create(0);
        Array* a1 = create(10);
        Array* a2 = create(20);
        Array* a3 = create(30);
        Node* list = NULL;
        list = sllist_insert(list, 1, a1);
        assert(list == NULL);
        list = sllist_insert(list, 0, a1);
        assert(sllist_length(list) == 1);
        assert(sllist_get(list, 0) == a1);
        list = sllist_insert(list, 0, a0);
        assert(sllist_length(list) == 2);
        assert(sllist_get(list, 0) == a0);
        assert(sllist_get(list, 1) == a1);
        list = sllist_insert(list, 3, a3);
        assert(sllist_length(list) == 2);
        list = sllist_insert(list, 2, a3);
        assert(sllist_length(list) == 3);
        assert(sllist_get(list, 2) == a3);
        list = sllist_insert(list, 2, a2);
        assert(sllist_length(list) == 4);
        assert(sllist_get(list, 2) == a2);
        assert(sllist_get(list, 3) == a3);
        assert(sllist_get(list, 0) == a0);
        assert(sllist_get(list, 1) == a1);
        
        list = sllist_delete(list, 10, destroy);
        assert(sllist_length(list) == 4);
        list = sllist_delete(list, 2, destroy);
        assert(sllist_length(list) == 3);
        assert(sllist_get(list, 2) == a3);
        assert(sllist_get(list, 1) == a1);
        assert(sllist_get(list, 0) == a0);
        list = sllist_delete(list, 0, destroy);
        assert(sllist_length(list) == 2);
        assert(sllist_get(list, 0) == a1);
        assert(sllist_get(list, 1) == a3);
        list = sllist_delete(list, 1, destroy);
        assert(sllist_length(list) == 1);
        assert(sllist_get(list, 0) == a1);
        list = sllist_delete(list, 0, destroy);
        assert(list == NULL);
    }
    //find
    {
        Array* a0 = create(0);
        Array* a1 = create(0);
        Array* a2 = create(10);
        Array* a3 = create(10);
        Array* a4 = create(20);
        Array* b0 = create(0);
        Array* b1 = create(10);
        Array* b2 = create(20);
        Array* b3 = create(30);
        Node* list = NULL;
        list = sllist_append(list, a0);
        list = sllist_append(list, a1);
        list = sllist_append(list, a2);
        list = sllist_append(list, a3);
        list = sllist_append(list, a4);
        assert(sllist_find(list, b3, compare) == -1);
        assert(sllist_find(list, b0, compare) == 0);
        assert(sllist_find(list, b1, compare) == 2);
        assert(sllist_find(list, b2, compare) == 4);
        sllist_delete_all(list, destroy);
        destroy(b0);
        destroy(b1);
        destroy(b2);
        destroy(b3);
    }
    //remove_first
    {
        Array* a0 = create(0);
        Array* a1 = create(0);
        Array* a2 = create(10);
        Array* a3 = create(10);
        Array* a4 = create(20);
        Array* b0 = create(0);
        Array* b1 = create(10);
        Array* b2 = create(20);
        Array* b3 = create(30);
        Node* list = NULL;
        list = sllist_append(list, a0);
        list = sllist_append(list, a1);
        list = sllist_append(list, a2);
        list = sllist_append(list, a3);
        list = sllist_append(list, a4);

        list = sllist_remove_first(list, b3, compare, destroy);
        assert(sllist_length(list) == 5);
        list = sllist_remove_first(list, b1, compare, destroy);
        assert(sllist_length(list) == 4);
        assert(sllist_get(list, 1) == a1);
        assert(sllist_get(list, 2) == a3);
        list = sllist_remove_first(list, b0, compare, destroy);
        assert(sllist_length(list) == 3);
        assert(sllist_get(list, 0) == a1);
        list = sllist_remove_first(list, b2, compare, destroy);
        assert(sllist_length(list) == 2);
        assert(sllist_get_last(list) == a3);

        sllist_delete_all(list, destroy);
        destroy(b0);
        destroy(b1);
        destroy(b2);
        destroy(b3);
    }
    //remove_all
    {
        Array* a0 = create(0);
        Array* a1 = create(0);
        Array* a2 = create(10);
        Array* a3 = create(10);
        Array* a4 = create(20);
        Array* b0 = create(0);
        Array* b1 = create(10);
        Array* b2 = create(20);
        Array* b3 = create(30);
        Node* list = NULL;
        list = sllist_append(list, a0);
        list = sllist_append(list, a1);
        list = sllist_append(list, a2);
        list = sllist_append(list, a3);
        list = sllist_append(list, a4);

        list = sllist_remove_all(list, b3, compare, destroy);
        assert(sllist_length(list) == 5);
        list = sllist_remove_all(list, b1, compare, destroy);
        assert(sllist_length(list) == 3);
        assert(sllist_get(list, 1) == a1);
        assert(sllist_get(list, 2) == a4);
        list = sllist_remove_all(list, b0, compare, destroy);
        assert(sllist_length(list) == 1);
        assert(sllist_get(list, 0) == a4);
        list = sllist_remove_all(list, b2, compare, destroy);
        assert(sllist_length(list) == 0);

        sllist_delete_all(list, destroy);
        destroy(b0);
        destroy(b1);
        destroy(b2);
        destroy(b3);
    }
    //copy, concat, foreach, find_custom
    {
        Array* a0 = create(0);
        Array* a1 = create(0);
        Array* a2 = create(10);
        Array* a3 = create(10);
        Array* a4 = create(20);
        Node* list = NULL;
        list = sllist_append(list, a0);
        list = sllist_append(list, a1);
        list = sllist_append(list, a2);
        list = sllist_append(list, a3);
        list = sllist_append(list, a4);
        Node* list_copy;

        list_copy = sllist_copy(list, copy);
        assert(sllist_length(list_copy) == 5);
        for (int i = 0; i < 5; i += 1) {
            assert(((Array*)sllist_get(list, i))->size == ((Array*)sllist_get(list_copy, i))->size);
        }

        Node* concatenated;
        concatenated = sllist_concat(NULL, list);
        assert(sllist_length(concatenated) == 5);
        concatenated = sllist_concat(concatenated, NULL);
        assert(sllist_length(concatenated) == 5);
        concatenated = sllist_concat(concatenated, list_copy);
        assert(sllist_length(concatenated) == 10);
        for (int i = 0; i < 5; i += 1) {
            assert(((Array*)sllist_get(concatenated, i))->size == ((Array*)sllist_get(concatenated, i + 5))->size);
        }

        sllist_foreach(list, func);

        assert(sllist_find_custom(list, predicate) == 4);

        sllist_delete_all(list, destroy);
    }

    return 0;
}






