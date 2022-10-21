#ifndef _SLLHASH_H_
#define _SLLHASH_H_

#include <stddef.h>
#include "hlist.h"

typedef size_t (*HashFunc)(char*);
typedef void (*Destructor)(void*);

typedef struct HashTable {
    size_t size;
    HLnode **table;
    HashFunc hf;
    Destructor dtor;
} HashTable;

void ht_init(HashTable *ht, size_t size, HashFunc hf, Destructor dtor);

void ht_destroy(HashTable *ht);

void ht_set(HashTable *ht, char* key, void* data);

void* ht_get(HashTable *ht, char *key);

int ht_has(HashTable *ht, char *key);

void ht_delete(HashTable *ht, char *key);

void ht_traverse(HashTable *ht, void (*f)(char *key, void* data));

void ht_resize(HashTable *ht, size_t new_size);

size_t jenkins_one_at_a_time_hash(char* key);

#endif
