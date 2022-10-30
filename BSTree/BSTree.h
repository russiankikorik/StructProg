#include <stddef.h>

#ifndef _BSTREE_H_
#define _BSTREE_H_

typedef int (*Comparator)(void* data1, void* data2); //data1 - value stored

typedef struct tBSTNode {
    void* data;
    void* parent;
    void* left;
    void* right;
} BSTNode;

typedef struct tBST {
    BSTNode* root;
    Comparator cmp;
    size_t size;
} BST;

// Create empty tree
BST* bst_create(Comparator cmp);

size_t bst_size(BST *tree);

// Return data which was replaced by this insertion if any else NULL
void* bst_insert(BST* tree, void* data);

// Find element with equal data and return its data if any else NULL
void* bst_find(BST* tree, void* data);

// Delete node with equal data and return its data if any else NULL
void* bst_delete(BST* tree, void* data);

// Clear tree but do not destroy tree struct
void bst_clear(BST* tree);

// Completely destroy tree
void bst_destroy(BST* tree);

// Call foreach_func for every node's data in tree passing given extra_data
void bst_foreach(BST *tree,
                 void (*foreach_func)(void* data, void* extra_data),
                 void* extra_data);

#endif
