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
    return 0;
}
