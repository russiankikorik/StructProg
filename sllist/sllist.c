#include "sllist.h"
#include <stdlib.h>

Node* _make_node(void* data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

void _free_node(Node* node, void (*destroy)(void*)) {
    if (node != NULL) {
        if (node->data != NULL && destroy != NULL) {
            destroy(node->data);
        }
        free(node);
    }
}

int sllist_length(Node* list) {
    int length = 0;
    while (list != NULL) {
        length += 1;
        list = list->next;
    }
    return length;
}

Node* sllist_prepend(Node* list, void* data) {
    Node* node = _make_node(data);
    if (node != NULL) {
        node->next = list;
        list = node;
    }
    return list;
}

Node* sllist_append(Node* list, void* data) {
    if (list == NULL) {
        list = _make_node(data);
    } else {
        Node* node = list;
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = _make_node(data);
    }
    return list;
}

Node* sllist_delete_first(Node* list, void (*destroy)(void*)) {
    if (list != NULL) {
        Node* deleted = list;
        list = deleted->next;
        _free_node(deleted, destroy);
    }
    return list;
}

Node* sllist_delete_last(Node* list, void (*destroy)(void*)) {
    if (list == NULL) {}
    else if (list->next == NULL) {
        list = sllist_delete_first(list, destroy);
    }
    else {
        Node* node = list;
        Node* deleted = list->next;
        while (deleted->next != NULL) {
            node = node->next;
            deleted = deleted->next;
        }
        node->next = NULL;
        _free_node(deleted, destroy);
    }
    return list;
}

void* sllist_get(Node* list, int i) {
    Node* node = list;
    void* data = NULL;
    for (int j = 0; j < i && node != NULL; j += 1) {
        node = node->next;
    }
    if (node != NULL) {
        data = node->data;
    }
    return data;
}

void sllist_put(Node* list, int i, void* data, void (*destroy)(void*)) {
    Node* node = list;
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

Node* sllist_insert(Node* list, int i, void* data) {
    if (i == 0) {
        list = sllist_prepend(list, data);
    }
    else if (i > 0) {
        Node* appendto = list;
        for (int j = 1; j < i && appendto != NULL; j += 1) {
            appendto = appendto->next;
        }
        if (appendto != NULL) {
            Node* node = _make_node(data);
            node->next = appendto->next;
            appendto->next = node;
        }
    }
    return list;
}

Node* sllist_delete(Node* list, int i, void (*destroy)(void*)) {
    if (i == 0) {
        list = sllist_delete_first(list, destroy);
    }
    else if (i > 0) {
        Node* node = list;
        Node* deleted = NULL;
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

void sllist_delete_all(Node* list, void (*destroy)(void*)) {
    if (list != NULL) {
        Node* next;
        Node* deleted = list;
        while (deleted != NULL) {
            next = deleted->next;
            _free_node(deleted, destroy);
            deleted = next;
        }
    }
}

void* sllist_get_last(Node* list) {
    void* data = NULL;
    if (list != NULL) {
        while (list->next != NULL) {
            list = list->next;
        }
        data = list->data;
    }
    return data;
}

void sllist_put_last(Node* list, int i, void* data, void (*destroy)(void*)) {
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

int sllist_find(Node* list, void* data, int (*equals)(void*, void*)) {
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

Node* sllist_remove_first(
        Node* list,
        void* data,
        int (*equals)(void*, void*),
        void (*destroy)(void*)
        ) {
    if (equals != NULL) {
        if (list != NULL && ! equals(list->data, data)) {
            list = sllist_delete_first(list, destroy);
        }
        else if (list != NULL) {
            Node* node = list;
            Node* deleted = list->next;
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

Node* sllist_remove_all(
        Node* list,
        void* data,
        int (*equals)(void*, void*),
        void (*destroy)(void*)
        ) {
    //delete the value compared to list - get pranked
    if (equals != NULL) {
        while (list != NULL && ! equals(list->data, data)) {
            list = sllist_delete_first(list, destroy);
        }
        Node* node = list;
        Node* deleted = NULL;
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
//bad
Node* sllist_copy(Node* list, void* (*copy)(void*)) {
    Node* node = list;
    Node* list_copy = NULL;
    Node* node_copy = NULL;
    void* data_copy = NULL;
    while (node != NULL) {
        data_copy = copy(node->data);
        node_copy = _make_node(data_copy);
        if (node_copy == NULL) {
            list_copy = NULL;
            break;
        }
        list_copy = sllist_append(list_copy, node_copy);
        node = node->next;
    }
    return list_copy;
}



