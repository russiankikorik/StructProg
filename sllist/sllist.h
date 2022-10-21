#include <stdlib.h>

#ifndef _SLLIST_H_
#define _SLLIST_H_

typedef struct SLLnode {
    void* data;
    void* next;
} SLLnode;

SLLnode* _make_node(void* data); 

void _free_node(SLLnode* node, void (*destroy)(void*)); 

int sllist_length(SLLnode* list);

SLLnode* sllist_prepend(SLLnode* list, void* data);

SLLnode* sllist_append(SLLnode* list, void* data);

SLLnode* sllist_delete_first(SLLnode* list, void (*destroy)(void*));

SLLnode* sllist_delete_last(SLLnode* list, void (*destroy)(void*));

void* sllist_get(SLLnode* list, int i);

void sllist_put(SLLnode* list, int i, void* data, void (*destroy)(void*));

SLLnode* sllist_insert(SLLnode* list, int i, void* data);

SLLnode* sllist_delete(SLLnode* list, int i, void (*destroy)(void*));

void sllist_delete_all(SLLnode* list, void (*destroy)(void*));

void* sllist_get_last(SLLnode* list);

void sllist_put_last(SLLnode* list, void* data, void (*destroy)(void*));

// COMPARE function is similiar in behavior to that used in qsort
// WARNING: first argument of COMPARE is value contained in list!
int sllist_find(SLLnode* list, void* data, int (*compare)(void*, void*));

SLLnode* sllist_remove_first(
        SLLnode* list,
        void* data,
        int (*compare)(void*, void*),
        void (*destroy)(void*)
        );

SLLnode* sllist_remove_all(
        SLLnode* list,
        void* data,
        int (*compare)(void*, void*),
        void (*destroy)(void*)
        );

SLLnode* sllist_copy(SLLnode* list, void* (*copy)(void*));

SLLnode* sllist_concat(SLLnode* list1, SLLnode* list2);

void sllist_foreach(SLLnode* list, void (*func)(void*));

int sllist_find_custom(SLLnode* list, int (*predicate)(void*)); 

#endif
