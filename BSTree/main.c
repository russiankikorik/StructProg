#include "BSTree.h"
#include <stdio.h>
#include <assert.h>

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

int main() {
    BST* tree = bst_create(compare);
    int arr[] = {10, 6, 14, 4, 8, 12, 16};

    assert(NULL == bst_insert(tree, (void*)(arr)));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(NULL == bst_insert(tree, (void*)(arr + 1)));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(NULL == bst_insert(tree, (void*)(arr + 2)));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(NULL == bst_insert(tree, (void*)(arr + 3)));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(NULL == bst_insert(tree, (void*)(arr + 4)));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
/*
    assert(arr[0] == *((int*)bst_insert(tree, (void*)(arr))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(arr[1] == *((int*)bst_insert(tree, (void*)(arr + 1))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(arr[2] == *((int*)bst_insert(tree, (void*)(arr + 2))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(arr[3] == *((int*)bst_insert(tree, (void*)(arr + 3))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(arr[4] == *((int*)bst_insert(tree, (void*)(arr + 4))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");

    assert(arr[0] == *((int*)bst_find(tree, (void*)(arr))));
    assert(arr[1] == *((int*)bst_find(tree, (void*)(arr + 1))));
    assert(arr[2] == *((int*)bst_find(tree, (void*)(arr + 2))));
    assert(arr[3] == *((int*)bst_find(tree, (void*)(arr + 3))));
    assert(arr[4] == *((int*)bst_find(tree, (void*)(arr + 4))));
*/
    /*
    assert(arr[0] == *((int*)bst_delete(tree, (void*)(arr))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(arr[1] == *((int*)bst_delete(tree, (void*)(arr + 1))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(arr[2] == *((int*)bst_delete(tree, (void*)(arr + 2))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(arr[3] == *((int*)bst_delete(tree, (void*)(arr + 3))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    assert(arr[4] == *((int*)bst_delete(tree, (void*)(arr + 4))));
    printf("%ld\n", bst_size(tree));
    bst_foreach(tree, printer, NULL);
    printf("\n");
    */
    bst_destroy(tree);
    return 0;
}
