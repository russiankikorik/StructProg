#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash.h"
#include <time.h>

typedef struct tEntry {
    size_t* arr;
} Entry;

void destroy (void* entry) {
    free(((Entry*)entry)->arr);
    free(entry);
}

Entry* init_entry(size_t value) {
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->arr = (size_t*)malloc(sizeof(size_t));
    (entry->arr)[0] = value;
    return entry;
}

void printer(char* key, void* data) {
    printf("%s", key);
    printf(" %ld\n", (((Entry*)data)->arr)[0]); 
}

char** mk_keys(size_t number, size_t len ) {
    char** arr = (char**)malloc(sizeof(char*) * number);
    srand(time(NULL));
    for (size_t i = 0; i < number; i += 1) {
        arr[i] = (char*)malloc(len + 1);
        for (size_t j = 0; j < len; j += 1) {
            arr[i][j] = 32 + rand() % 95;
        }
    }
    for (size_t i = 0; i < number; i += 1) {
        arr[i][len] = 0;
    }
    return arr;
}

void free_keys(char** arr, size_t number) {
    for (size_t i = 0; i < number; i += 1) {
        free(arr[i]);
    }
    free(arr);
}

void mytest(size_t size, size_t number, size_t len) {
    printf("size %ld number %ld len %ld\n", size, number, len);
    char** keys = mk_keys(number, len);
    clock_t t0, t1, dt, sum;
    HashTable ht;
    ht_init(&ht, size, NULL, destroy);
    t0 = clock();
    for (size_t i = 0; i < number; i += 1) {
        Entry* entry = init_entry(i);
        ht_set(&ht, keys[i], entry);
    }
    t1 = clock();
    dt = t1 - t0;
    printf("%.10f init time for size %ld\n",
            (float)dt / (float)CLOCKS_PER_SEC, size);
    sum = 0;
    for (size_t i = 0; i < number; i += 1) {
        t0 = clock();
        Entry* entry = (Entry*)ht_get(&ht, keys[i]);
        assert((entry->arr)[0] == i);
        t1 = clock();
        dt = t1 - t0;
        sum += dt;
    }
    printf("%.10f average access time for size %ld\n",
            (float)sum / (float)CLOCKS_PER_SEC / (float)number, size);
    for (size_t i = 0; i < number; i += 1) {
        assert(ht_has(&ht, keys[i]));
    }

    sum = 0;
    for (size_t i = 0; i < number; i += 1) {
        t0 = clock();
        ht_delete(&ht, keys[i]);
        t1 = clock();
        dt = t1 - t0;
        sum += dt;
        assert(NULL == ht_get(&ht, keys[i]));
        /*
        for (size_t j = i + 1; j < number; j += 1) {
            Entry* entry = (Entry*)ht_get(&ht, keys[j]);
            assert((entry->arr)[0] == j);
        }
        */

    }
    printf("%.10f average deletion time for size %ld\n",
            (float)sum / (float)CLOCKS_PER_SEC / (float)number, size);
    for (size_t i = 0; i < number; i += 1) {
        assert(!ht_has(&ht, keys[i]));
    }


    free_keys(keys, number);
    ht_destroy(&ht);

}    

void resize_test(size_t size, size_t number, size_t len) {
    printf("size %ld number %ld len %ld\n", size, number, len);
    char** keys = mk_keys(number, len);
    clock_t t0, t1, dt;
    HashTable ht;
    ht_init(&ht, size, NULL, destroy);
    for (size_t i = 0; i < number; i += 1) {
        Entry* entry = init_entry(i);
        ht_set(&ht, keys[i], entry);
    }
    t0 = clock();
    ht_resize(&ht, size * 10);
    t1 = clock();
    dt = t1 - t0;
    for (size_t i = 0; i < number; i += 1) {
        Entry* entry = (Entry*)ht_get(&ht, keys[i]);
        assert((entry->arr)[0] == i);
    }
    printf("%.10f size x10 resize time\n",
            (float)dt / (float)CLOCKS_PER_SEC);
    t0 = clock();
    ht_resize(&ht, size);
    t1 = clock();
    dt = t1 - t0;
    for (size_t i = 0; i < number; i += 1) {
        Entry* entry = (Entry*)ht_get(&ht, keys[i]);
        assert((entry->arr)[0] == i);
    }
    printf("%.10f size x10 backward resize time\n",
            (float)dt / (float)CLOCKS_PER_SEC);
    t0 = clock();
    ht_resize(&ht, size * 100);
    t1 = clock();
    dt = t1 - t0;
    for (size_t i = 0; i < number; i += 1) {
        Entry* entry = (Entry*)ht_get(&ht, keys[i]);
        assert((entry->arr)[0] == i);
    }
    printf("%.10f size x100 resize time\n",
            (float)dt / (float)CLOCKS_PER_SEC);
    t0 = clock();
    ht_resize(&ht, size);
    t1 = clock();
    dt = t1 - t0;
    for (size_t i = 0; i < number; i += 1) {
        Entry* entry = (Entry*)ht_get(&ht, keys[i]);
        assert((entry->arr)[0] == i);
    }
    printf("%.10f size x100 backward resize time\n",
            (float)dt / (float)CLOCKS_PER_SEC);
    t0 = clock();
    ht_resize(&ht, size * 1000);
    t1 = clock();
    dt = t1 - t0;
    for (size_t i = 0; i < number; i += 1) {
        Entry* entry = (Entry*)ht_get(&ht, keys[i]);
        assert((entry->arr)[0] == i);
    }
    printf("%.10f size x1000 resize time\n",
            (float)dt / (float)CLOCKS_PER_SEC);
    t0 = clock();
    ht_resize(&ht, size);
    t1 = clock();
    dt = t1 - t0;
    for (size_t i = 0; i < number; i += 1) {
        Entry* entry = (Entry*)ht_get(&ht, keys[i]);
        assert((entry->arr)[0] == i);
    }
    printf("%.10f size x1000 backward resize time\n",
            (float)dt / (float)CLOCKS_PER_SEC);
    free_keys(keys, number);
    ht_destroy(&ht);
}


int main() {
    {
        size_t number, len, size;
        
        number = 1000000;
        len = 10;
        
        size = 10000;
        mytest(size, number, len);
        printf("\n");
        size = 100000;
        mytest(size, number, len);
        printf("\n");
        size = 1000000;
        mytest(size, number, len);
        printf("\n");
        size = 10000000;
        mytest(size, number, len);
        printf("\n");
        size = 100000000;
        mytest(size, number, len);
        printf("\n");
        size = 100000000;
        mytest(size, number, len);
        printf("\n");

        resize_test(10000, number, len);
    }

    HashTable ht;
    ht_init(&ht, 10, NULL, destroy);
    char** keys = mk_keys(10, 10);
    for (size_t i = 0; i < 10; i += 1) {
        Entry* entry = init_entry(i);
        ht_set(&ht, keys[i], entry);
    }
    ht_traverse(&ht, printer);
    free_keys(keys, 10);
    ht_destroy(&ht);

    return 0;
}






