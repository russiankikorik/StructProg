#include "BSTree.h"
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int compare(void* data1, void* data2) {
    int* d1 = (int*)data1;
    int* d2 = (int*)data2;
    if (*d1 < *d2) {return -1;}
    else if (*d1 == *d2) {return 0;}
    else {return 1;}
}

void printer(void* data, void* extra_data) {
    printf("%d ", *((int*)data));
}

void insert_test(BST* tree, int* arr, int i, size_t size) {
    assert(NULL == bst_insert(tree, (void*)(arr + i)));
    assert(arr[i] == *((int*)bst_insert(tree, (void*)(arr + i))));
    assert(arr[i] == *((int*)bst_find(tree, (void*)(arr + i))));
    assert(size == bst_size(tree));
}

void delete_test(BST* tree, int* arr, int i, size_t size) {
    assert(arr[i] == *((int*)bst_delete(tree, (void*)(arr + i))));
    assert(NULL == bst_find(tree, (void*)(arr + i)));
    assert(size == bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
}

void shuffle(int* a, size_t n) {
    srand(time(NULL));
    int buf;
    size_t j;
    for (size_t i = n - 1; i > 0; i -= 1) {
        j = rand() % (i + 1);
        buf = a[i];
        a[i] = a[j];
        a[j] = buf;
    }
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

void strshuffle(char** a, size_t n) {
    srand(time(NULL));
    char* buf;
    size_t j;
    for (size_t i = n - 1; i > 0; i -= 1) {
        j = rand() % (i + 1);
        buf = a[i];
        a[i] = a[j];
        a[j] = buf;
    }
}

int main() {
    {
        //leaves
        BST* tree = bst_create(compare);
        int arr[] = {10, 8, 9};

        insert_test(tree, arr, 0, 1);
        insert_test(tree, arr, 1, 2);
        insert_test(tree, arr, 2, 3);

        printf("test 1 tree\n");
        bst_foreach(tree, printer, NULL);
        printf("\n");

        delete_test(tree, arr, 2, 2); //9
        delete_test(tree, arr, 1, 1); //8

        printf("root removed\n");
        delete_test(tree, arr, 0, 0);
        bst_destroy(tree);
    }
    {
        //single ancestor
        BST* tree = bst_create(compare);
        int arr[] = {10, 14, 20, 18, 16, 17};

        insert_test(tree, arr, 0, 1);
        insert_test(tree, arr, 1, 2);
        insert_test(tree, arr, 2, 3);
        insert_test(tree, arr, 3, 4);
        insert_test(tree, arr, 4, 5);
        insert_test(tree, arr, 5, 6);

        printf("test 2 tree\n");
        bst_foreach(tree, printer, NULL);
        printf("\n");

        delete_test(tree, arr, 4, 5); //16
        delete_test(tree, arr, 3, 4); //18
        delete_test(tree, arr, 2, 3); //20
        delete_test(tree, arr, 1, 2); //14

        printf("root removed\n");
        delete_test(tree, arr, 0, 1);
        bst_destroy(tree);
    }
    {
        //two ancestors, right with no left
        BST* tree = bst_create(compare);
        int arr[] = {10, 5, 15, 4, 6, 14, 16, 7, 17};

        insert_test(tree, arr, 0, 1);
        insert_test(tree, arr, 1, 2);
        insert_test(tree, arr, 2, 3);
        insert_test(tree, arr, 3, 4);
        insert_test(tree, arr, 4, 5);
        insert_test(tree, arr, 5, 6);
        insert_test(tree, arr, 6, 7);
        insert_test(tree, arr, 7, 8);
        insert_test(tree, arr, 8, 9);

        printf("test 3 tree\n");
        bst_foreach(tree, printer, NULL);
        printf("\n");

        delete_test(tree, arr, 1, 8); //5
        delete_test(tree, arr, 2, 7); //15
       
        printf("root removed\n");
        delete_test(tree, arr, 0, 6);
        bst_destroy(tree);
    }
    {
        //two ancestors, right with no left
        BST* tree = bst_create(compare);
        int arr[] = {10, 6, 14, 4, 8, 12, 16, 7, 15};

        insert_test(tree, arr, 0, 1);
        insert_test(tree, arr, 1, 2);
        insert_test(tree, arr, 2, 3);
        insert_test(tree, arr, 3, 4);
        insert_test(tree, arr, 4, 5);
        insert_test(tree, arr, 5, 6);
        insert_test(tree, arr, 6, 7);
        insert_test(tree, arr, 7, 8);
        insert_test(tree, arr, 8, 9);

        printf("test 4 tree\n");
        bst_foreach(tree, printer, NULL);
        printf("\n");

        delete_test(tree, arr, 1, 8); //6
        delete_test(tree, arr, 2, 7); //14
       
        bst_destroy(tree);
    }
    {
        clock_t t1, t0, dt;
        BST* tree = bst_create(compare);
        size_t size = 1000000;
        int* a = malloc(size * sizeof(int));
        for (int i = 0; i < size; i += 1) {
            a[i] = i;
        }
        shuffle(a, size);
        int* acpy = malloc(size * sizeof(int));
        for (int i = 0; i < size; i += 1) {
            acpy[i] = a[i];
        }
        for (int i = 1; i <= size; i *= 10) {
            t0 = clock();
            for (int j = 0; j < i; j += 1) {
                assert(NULL == bst_insert(tree, (void*)(a + j)));
            }
            t1 = clock();
            dt = t1 - t0;
            printf("insertion time for %d elements %f\n", i, (float)dt/(float)CLOCKS_PER_SEC);
            shuffle(acpy, i);
            t0 = clock();
            for (int j = 0; j < i; j += 1) {
                assert(a + j == bst_delete(tree, (void*)(a + j)));
            }
            t1 = clock();
            dt = t1 - t0;
            printf("deletion time for %d elements %f\n", i, (float)dt/(float)CLOCKS_PER_SEC);
        }
        bst_destroy(tree);
        free(a);
        free(acpy);
    }
    /*
    {
        size_t size = 1000000;
        char** arr = mk_keys(size, 10);
        clock_t t1, t0, dt;
        BST* tree = bst_create(strcmp);
        for (int i = 1; i <= size; i *= 10) {
            t0 = clock();
            for (int j = 0; j < i; j += 1) {
                bst_insert(tree, (void*)(arr + j));
            }
            t1 = clock();
            dt = t1 - t0;
            printf("insertion time for %d elements %f\n", i, (float)dt/(float)CLOCKS_PER_SEC);
            t0 = clock();
            for (int j = 0; j < i; j += 1) {
                bst_delete(tree, (void*)(arr + j));
            }
            t1 = clock();
            dt = t1 - t0;
            printf("deletion time for %d elements %f\n", i, (float)dt/(float)CLOCKS_PER_SEC);
        }
        bst_destroy(tree);
        free_keys(arr, size);
    }
    */
    return 0;
}
