#ifndef _HLIST_H_
#define _HLIST_H_

typedef struct _HLnode {
    char* key;
    void* data;
    void* next;
} HLnode;

HLnode* hlist_insert(
        HLnode* list,
        char* key,
        void* data,
        void (*destroy)(void*)
        );

HLnode* hlist_delete(HLnode* list, char* key, void (*destroy)(void*));

void* hlist_get(HLnode* list, char* key);

int hlist_has(HLnode* list, char* key);

void hlist_foreach(HLnode* list, void (*func)(char *key, void* data));

HLnode* hlist_delete_all(HLnode* list, void (*destroy)(void*));
#endif
