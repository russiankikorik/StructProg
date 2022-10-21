#include <stdlib.h>
#include "hash.h"

size_t jenkins_one_at_a_time_hash(char *key) {
    size_t hash = 0;

    for (; *key; ++key) {
        hash += *key;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

void ht_init(HashTable *ht, size_t size, HashFunc hf, Destructor dtor) {
    if (hf == NULL) {
        hf = jenkins_one_at_a_time_hash;
    }
    ht->hf = hf;
    ht->size = size;
    ht->dtor = dtor;
    ht->table = (HLnode**)malloc(sizeof(HLnode*) * size);
    for (int i; i < size; i += 1) {
        (ht->table)[i] = NULL;
    }
}

void ht_destroy(HashTable *ht) {
    if (ht->table != NULL) {
        for (int i = 0; i < ht->size; i += 1) {
            hlist_delete_all((ht->table)[i], ht->dtor);
        }
        ht->size = 0;
        free(ht->table);
        ht->table = NULL;
    }
}

void ht_set(HashTable *ht, char* key, void* data) {
    if (ht->table != NULL && ht->size != 0 && ht->hf != NULL) {
        size_t index = ((ht->hf)(key)) % ht->size;
        (ht->table)[index] = hlist_insert(
                (ht->table)[index],
                key,
                data,
                ht->dtor);
    }
}

void* ht_get(HashTable* ht, char* key) {
    void* data = NULL;
    if (ht->table != NULL && ht->size != 0 && ht->hf != NULL) {
        size_t index = ((ht->hf)(key)) % ht->size;
        data = hlist_get(((ht->table)[index]), key);
    }
    return data;
}

int ht_has(HashTable* ht, char* key) {
    int has = 0;
    if (ht->table != NULL && ht->size != 0 && ht->hf != NULL) {
        size_t index = ((ht->hf)(key)) % ht->size;
        has = hlist_has(((ht->table)[index]), key);
    }
    return has;
}

void ht_delete(HashTable* ht, char* key) {
    if (ht->table != NULL && ht->size != 0 && ht->hf != NULL) {
        size_t index = ((ht->hf)(key)) % ht->size;
        (ht->table)[index] = hlist_delete((ht->table)[index], key, ht->dtor);
    }
}

void ht_traverse(HashTable* ht, void (*f)(char* key, void* data)) {
    if (ht->table != NULL && ht->size != 0 && ht->hf != NULL) {
        for (int i = 0; i < ht->size; i += 1) {
            hlist_foreach((ht->table)[i], f);
        }
    }
}

void ht_resize(HashTable* ht, size_t new_size) {
    if (ht->table != NULL &&
            ht->size != 0 &&
            ht->hf != NULL &&
            new_size > 0 &&
            new_size != ht->size) {
        HLnode** new_table = (HLnode**)malloc(sizeof(HLnode*) * new_size);
        for (int i = 0; i < new_size; i += 1) {
            new_table[i] = NULL;
        }
        size_t index;
        for (int i = 0; i < ht->size; i += 1) {
            HLnode* list = (ht->table)[i];
            HLnode* node = list;
            while (node != NULL) {
                index = ((ht->hf)(node->key)) % new_size;
                new_table[index] = hlist_insert(
                        new_table[index],
                        node->key,
                        node->data,
                        NULL
                        );
                node = node->next;
            }
            hlist_delete_all(list, NULL);
        }
        free(ht->table);
        ht->table = new_table;
        ht->size = new_size;
    }
}

                
























