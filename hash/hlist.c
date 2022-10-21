#include <stdlib.h>
#include <string.h>
#include "hlist.h"

static HLnode* _make_node(char* key, void* data) {
    HLnode* node = NULL;
    if (key != NULL) {
        node = (HLnode*)malloc(sizeof(HLnode));
        if (node != NULL) {
            node->key = malloc(strlen(key) + 1);
            strcpy(node->key, key);
            node->data = data;
            node->next = NULL;
        }
    }
    return node;
}

static void _free_node(HLnode* node, void (*destroy)(void*)) {
    if (node != NULL) {
        if (node->data != NULL && destroy != NULL) {
            destroy(node->data);
        }
        free(node->key);
        free(node);
    }
}

HLnode* hlist_insert(
        HLnode* list,
        char* key,
        void* data,
        void (*destroy)(void*)
        ) {
    if (key != NULL && list != NULL) {
        HLnode* node = list;
        while (node != NULL && strcmp(key, node->key) != 0) {
            node = node->next;
        }
        if (node != NULL) {
            if(destroy != NULL) {
                destroy(node->data);
            }
            node->data = data;
        } else {
            HLnode* new = _make_node(key, data);
            new->next = list;
            list = new;
        }
    }
    else if (key != NULL) {
        list = _make_node(key, data);
    }
    return list;
}

HLnode* hlist_delete(HLnode* list, char* key, void (*destroy)(void*)) {
    if (key != NULL && list != NULL) {
        HLnode* node = list;
        if (strcmp(node->key, key) == 0) {
            list = list->next;
            _free_node(node, destroy);
        } else {
            HLnode* deleted = node->next;
            while (deleted != NULL && strcmp(key, deleted->key) != 0) {
                node = node->next;
                deleted = deleted->next;
            }
            if (deleted != NULL) {
                node->next = deleted->next;
                _free_node(deleted, destroy);
            }
        }
    }
    return list;
}

void* hlist_get(HLnode* list, char* key) {
    void* data = NULL;
    if (key != NULL && list != NULL) {
        HLnode* node = list;
        while (node != NULL && strcmp(key, node->key) != 0) {
            node = node->next;
        }
        if (node != NULL) {
            data = node->data;
        }
    }
    return data;
}

int hlist_has(HLnode* list, char* key) {
    int has = 0;
    if (key != NULL && list != NULL) {
        HLnode* node = list;
        while (node != NULL && strcmp(key, node->key) != 0) {
            node = node->next;
        }
        if (node != NULL) {
            has = 1;
        }
    }
    return has;
}

void hlist_foreach(HLnode* list, void (*func)(char *key, void* data)) {
    if (func != NULL) {
        while (list != NULL) {
            func(list->key, list->data);
            list = list->next;
        }
    }
}

HLnode* hlist_delete_all(HLnode* list, void (*destroy)(void*)) {
    HLnode* node;
    while (list != NULL) {
        node = list;
        list = list->next;
        _free_node(node, destroy);
    }
    return NULL;
}
