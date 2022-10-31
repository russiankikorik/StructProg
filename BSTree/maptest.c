#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BSTree.h"
#include <assert.h>

typedef struct tEntry {
    char* key;
    void* value;
} Entry;

int compare(void* data1, void* data2) {
    Entry* entry1 = (Entry*)data1;
    Entry* entry2 = (Entry*)data2;
    return strcmp(entry1->key, entry2->key);
}

void* insert_entry(BST* tree, char* key, void* value) {
    int len = strlen(key);
    char* inserted_key = (char*)malloc(len + 1);
    strcpy(inserted_key, key);
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->key = inserted_key;
    entry->value = value;
    Entry* old_entry = bst_insert(tree, (void*)entry);
    void* returned = NULL;
    if (old_entry) {
        returned = old_entry->value;
        free(old_entry->key);
        free(old_entry);
    }
    return returned;
}

void* delete_entry(BST* tree, char* key) {
    Entry cmpentry;
    cmpentry.key = key;
    Entry* entry = (Entry*)bst_delete(tree, &cmpentry);
    void* returned = NULL;
    if (entry) {
        returned = entry->value;
        free(entry->key);
        free(entry);
    }
    return returned;
}

void* find_entry(BST* tree, char* key) {
    Entry cmpentry;
    cmpentry.key = key;
    Entry* entry = (Entry*)bst_find(tree, &cmpentry);
    void* returned = NULL;
    if (entry) {
        returned = entry->value;
    }
    return returned;
}

int main() {
    char* a = "abc";
    char* b = "abd";
    char* c = "ab";
    int ai = 1;
    int bi = 2;
    int ci = 3;

    BST* tree = bst_create(compare);

    assert(NULL == insert_entry(tree, a, &ai));
    assert(&ai == insert_entry(tree, a, &ai));
    assert(&ai == find_entry(tree, a));

    assert(NULL == insert_entry(tree, b, &bi));
    assert(&bi == insert_entry(tree, b, &bi));
    assert(&bi == find_entry(tree, b));

    assert(NULL == insert_entry(tree, c, &ci));
    assert(&ci == insert_entry(tree, c, &ci));
    assert(&ci == find_entry(tree, c));

    assert(&ai == delete_entry(tree, a));
    assert(NULL == find_entry(tree, a));

    assert(&bi == delete_entry(tree, b));
    assert(NULL == find_entry(tree, b));

    assert(&ci == delete_entry(tree, c));
    assert(NULL == find_entry(tree, c));

    bst_destroy(tree);

    return 0;

}
