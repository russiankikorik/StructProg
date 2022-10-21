#include "sllist.h"
#include <stdlib.h>

SLLnode* _make_node(void* data) {
    SLLnode* node = (SLLnode*)malloc(sizeof(SLLnode));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

void _free_node(SLLnode* node, void (*destroy)(void*)) {
    if (node != NULL) {
        if (node->data != NULL && destroy != NULL) {
            destroy(node->data);
        }
        free(node);
    }
}

int sllist_length(SLLnode* list) {
    int length = 0;
    while (list != NULL) {
        length += 1;
        list = list->next;
    }
    return length;
}

SLLnode* sllist_prepend(SLLnode* list, void* data) {
    SLLnode* node = _make_node(data);
    if (node != NULL) {
        node->next = list;
        list = node;
    }
    return list;
}

SLLnode* sllist_append(SLLnode* list, void* data) {
    if (list == NULL) {
        list = _make_node(data);
    } else {
        SLLnode* node = list;
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = _make_node(data);
    }
    return list;
}

SLLnode* sllist_delete_first(SLLnode* list, void (*destroy)(void*)) {
    if (list != NULL) {
        SLLnode* deleted = list;
        list = deleted->next;
        _free_node(deleted, destroy);
    }
    return list;
}

SLLnode* sllist_delete_last(SLLnode* list, void (*destroy)(void*)) {
    if (list == NULL) {}
    else if (list->next == NULL) {
        list = sllist_delete_first(list, destroy);
    }
    else {
        SLLnode* node = list;
        SLLnode* deleted = list->next;
        while (deleted->next != NULL) {
            node = node->next;
            deleted = deleted->next;
        }
        node->next = NULL;
        _free_node(deleted, destroy);
    }
    return list;
}

void* sllist_get(SLLnode* list, int i) {
    SLLnode* node = list;
    void* data = NULL;
    for (int j = 0; j < i && node != NULL; j += 1) {
        node = node->next;
    }
    if (node != NULL) {
        data = node->data;
    }
    return data;
}

void sllist_put(SLLnode* list, int i, void* data, void (*destroy)(void*)) {
    SLLnode* node = list;
    for (int j = 0; j < i && node != NULL; j += 1) {
        node = node->next;
    }
    if (node != NULL) {
       if (destroy != NULL) {
          destroy(node->data);
       }
       node->data = data;
    }
}

SLLnode* sllist_insert(SLLnode* list, int i, void* data) {
    if (i == 0) {
        list = sllist_prepend(list, data);
    }
    else if (i > 0) {
        SLLnode* appendto = list;
        for (int j = 1; j < i && appendto != NULL; j += 1) {
            appendto = appendto->next;
        }
        if (appendto != NULL) {
            SLLnode* node = _make_node(data);
            node->next = appendto->next;
            appendto->next = node;
        }
    }
    return list;
}

SLLnode* sllist_delete(SLLnode* list, int i, void (*destroy)(void*)) {
    if (i == 0) {
        list = sllist_delete_first(list, destroy);
    }
    else if (i > 0) {
        SLLnode* node = list;
        SLLnode* deleted = NULL;
        if (node != NULL) {
            deleted = node->next;
        }
        for (int j = 1; j < i && deleted != NULL; j += 1) {
            node = node->next;
            deleted = deleted->next;
        }
        if (deleted != NULL) {
            node->next = deleted->next;
            _free_node(deleted, destroy);
        }
    }
    return list;
}

void sllist_delete_all(SLLnode* list, void (*destroy)(void*)) {
    if (list != NULL) {
        SLLnode* next;
        SLLnode* deleted = list;
        while (deleted != NULL) {
            next = deleted->next;
            _free_node(deleted, destroy);
            deleted = next;
        }
    }
}

void* sllist_get_last(SLLnode* list) {
    void* data = NULL;
    if (list != NULL) {
        while (list->next != NULL) {
            list = list->next;
        }
        data = list->data;
    }
    return data;
}

void sllist_put_last(SLLnode* list, void* data, void (*destroy)(void*)) {
    if (list != NULL) {
        while (list->next != NULL) {
            list = list->next;
        }
        if (destroy != NULL) {
            destroy(list->data);
        }
        list->data = data;
    }
}

int sllist_find(SLLnode* list, void* data, int (*equals)(void*, void*)) {
    int i = 0;
    if (equals != NULL) {
        for (; list != NULL && /*!*/equals(list->data, data); i += 1) {
            list = list->next;
        }
        if (list == NULL) {
            i = -1;
        }
    } else {
        i = -1;
    }
    return i;
}

SLLnode* sllist_remove_first(
        SLLnode* list,
        void* data,
        int (*equals)(void*, void*),
        void (*destroy)(void*)
        ) {
    if (equals != NULL) {
        if (list != NULL && ! equals(list->data, data)) {
            list = sllist_delete_first(list, destroy);
        }
        else if (list != NULL) {
            SLLnode* node = list;
            SLLnode* deleted = list->next;
            while (deleted != NULL && /*!*/equals(deleted->data, data)) {
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

SLLnode* sllist_remove_all(
        SLLnode* list,
        void* data,
        int (*equals)(void*, void*),
        void (*destroy)(void*)
        ) {
    //delete the value compared to list - get pranked
    if (equals != NULL) {
        while (list != NULL && ! equals(list->data, data)) {
            list = sllist_delete_first(list, destroy);
        }
        SLLnode* node = list;
        SLLnode* deleted = NULL;
        if (node != NULL) {
            deleted = node->next;
        }
        while (deleted != NULL) {
            if ( ! equals(deleted->data, data)) {
                node->next = deleted->next;
                _free_node(deleted, destroy);
                deleted = node->next;
            } else {
                node = node->next;
                deleted = deleted->next;
            }
        }
    }
    return list;
}

SLLnode* sllist_copy(SLLnode* list, void* (*copy)(void*)) {
    SLLnode* list_copy = NULL;
    if (copy != NULL) {
        SLLnode* node = list;
        void* data_copy = NULL;
        while (node != NULL) {
            data_copy = copy(node->data);
            list_copy = sllist_append(list_copy, data_copy);
            node = node->next;
        }
    }
    return list_copy;
}

SLLnode* sllist_concat(SLLnode* list1, SLLnode* list2) {
    SLLnode* list = list1;
    if (list != NULL) {
        SLLnode* node = list;
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = list2;
    } else {
        list = list2;
    }
    return list;
}

void sllist_foreach(SLLnode* list, void (*func)(void*)) {
    if (func != NULL) {
        while (list != NULL) {
            func(((SLLnode*)list)->data);
            list = list->next;
        }
    }
}

int sllist_find_custom(SLLnode* list, int (*predicate)(void*)) {
    int i = 0;
    if (predicate != NULL) {
        for (; list != NULL && !predicate(list->data); i += 1) {
            list = list->next;
        }
        if (list == NULL) {
            i = -1;
        }
    } else {
        i = -1;
    }
    return i;
}
