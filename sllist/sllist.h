#include <stdlib.h>

typedef struct Node {
    void* data;
    void* next;
} Node;

Node* _make_node(void* data); 

void _free_node(Node* node, void (*destroy)(void*)); 

int sllist_length(Node* list);

Node* sllist_prepend(Node* list, void* data);

Node* sllist_append(Node* list, void* data);

Node* sllist_delete_first(Node* list, void (*destroy)(void*));

Node* sllist_delete_last(Node* list, void (*destroy)(void*));

void* sllist_get(Node* list, int i);

void sllist_put(Node* list, int i, void* data, void (*destroy)(void*));

Node* sllist_insert(Node* list, int i, void* data);

Node* sllist_delete(Node* list, int i, void (*destroy)(void*));

void sllist_delete_all(Node* list, void (*destroy)(void*));

void* sllist_get_last(Node* list);

void sllist_put_last(Node* list, int i, void* data, void (*destroy)(void*));

int sllist_find(Node* list, void* data, int (*compare)(void*, void*));

Node* sllist_remove_first(
        Node* list,
        void* data,
        int (*compare)(void*, void*),
        void (*destroy)(void*)
        );

Node* sllist_remove_all(
        Node* list,
        void* data,
        int (*compare)(void*, void*),
        void (*destroy)(void*)
        );

Node* sllist_copy(Node* list, void* (*copy)(void*));

Node* sllist_concat(Node* list1, Node* list2);

void sllist_foreach(Node* list, void (*func)(void*));

int sllist_find_custom(Node* list, int (*predicate)(void*)); 
