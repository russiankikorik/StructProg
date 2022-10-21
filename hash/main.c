#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash.h"

typedef struct tEntry {
    int* arr;
} Entry;

void destroy (void* entry) {
    free(((Entry*)entry)->arr);
}

void init_entry(Entry* entry, int value) {
    entry->arr = (int*)malloc(sizeof(int));
    (entry->arr)[0] = value;
}

void printer(char* key, void* data) {
    printf("%s", key);
    printf(" %d\n", (((Entry*)data)->arr)[0]); 
}

int main() {
    HashTable ht;
    ht_init(&ht, 2, NULL, destroy);

    Entry e1;
    init_entry(&e1, 1);
    char* k1 = "lol";

    Entry e2;
    init_entry(&e2, 2);
    char* k2 = "kek";

    Entry e3;
    init_entry(&e3, 3);
    char* k3 = "cheburek";

    Entry e4;
    init_entry(&e4, 4);
    char* k4 = "ahaha";

    Entry e5;
    init_entry(&e5, 5);
    char* k5 = "lol";

    ht_set(&ht, k2, &e2);
    ht_traverse(&ht, printer);
    printf("\n");

    ht_set(&ht, k3, &e3);
    ht_traverse(&ht, printer);
    printf("\n");

    ht_set(&ht, k4, &e4);
    ht_traverse(&ht, printer);
    printf("\n");

    ht_set(&ht, k5, &e5);
    ht_traverse(&ht, printer);
    printf("\n");

    ht_set(&ht, k1, &e1);
    ht_traverse(&ht, printer);
    printf("\n");

    ht_delete(&ht, "lol");
    ht_traverse(&ht, printer);
    printf("\n");

    assert((((Entry*)(ht_get(&ht, k4)))->arr)[0] == 4);
    assert(ht_get(&ht, k5) == NULL);
    assert(ht_has(&ht, k1) == 0);
    assert(ht_has(&ht, k2) == 1);

    ht_resize(&ht, 10);
    ht_traverse(&ht, printer);
    ht_resize(&ht, 1);
    ht_traverse(&ht, printer);

    ht_destroy(&ht);
    return 0;
}






