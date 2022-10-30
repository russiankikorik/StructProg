#include <stdlib.h>
#include "BSTree.h"

static BST* _make_tree(Comparator cmp) {
    BST* tree = malloc(sizeof(BST));
    tree->root = NULL;
    tree->cmp = cmp;
    tree->size = 0;
    return tree;
}

static void _free_tree(BST* tree) {
    free(tree);
}

static BSTNode* _make_node(void* data) {
    BSTNode* node = malloc(sizeof(BSTNode));
    node->data = data;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void _free_node(BSTNode* node) {
    if (node != NULL) {
        free(node);
    }
}

static BSTNode* _sub_min(BSTNode* subroot) {
    while (subroot->left != NULL) {
        subroot = subroot->left;
    }
    return subroot;
}

static BSTNode* _successor(BSTNode* node) {
    BSTNode* successor = NULL;
    if (node->right != NULL) {
        successor = _sub_min(node->right);
    } else {
        BSTNode* parent = node->parent;
        while (parent != NULL && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        successor = parent;
    }
    return successor;
}

static void _transplant(BST* tree, BSTNode* old, BSTNode* new) {
    if (old->parent == NULL) {
        tree->root = new;
    } else if (((BSTNode*)(old->parent))->left == old) {
        ((BSTNode*)(old->parent))->left = new;
    } else {
        ((BSTNode*)(old->parent))->right = new;
    }
    if (new != NULL) {
        new->parent = old->parent;
    }
}

static void _remove_node(BST* tree, BSTNode* node) {
    if (node->left == NULL) {
        _transplant(tree, node, (BSTNode*)(node->right));
    } else if (node->right == NULL) {
        _transplant(tree, node, (BSTNode*)(node->left));
    } else {
        BSTNode* repl = _sub_min((BSTNode*)(node->right));
        if (repl->parent != node) {
            _transplant(tree, repl, (BSTNode*)(repl->right));
            repl->right = node->right;
            ((BSTNode*)(node->right))->parent = repl;
        }
        _transplant(tree, node, repl);
        repl->left = node->left;
        ((BSTNode*)(node->left))->parent = repl;
    }
}

BST* bst_create(Comparator cmp) {
    return _make_tree(cmp);
}

size_t bst_size(BST* tree) {
    return tree->size;
}

void* bst_insert(BST* tree, void* data) {
    void* returned = NULL;
    if (tree->root == NULL) {
        tree->root = _make_node(data);
        tree->size += 1;
    } else {
        BSTNode* node = tree->root;
        BSTNode* parent = NULL;
        int cmpres = 0;
        while (node != NULL) {
            cmpres = (tree->cmp)(node->data, data);
            if (cmpres < 0) {
                parent = node;
                node = node->right;
            } else if (cmpres > 0) {
                parent = node;
                node = node->left;
            } else {break;}
        }
        if (node == NULL && cmpres < 0) {
            BSTNode* newnode = _make_node(data);
            newnode->parent = parent;
            parent->right = newnode;
            tree->size += 1;
        } else if (node == NULL && cmpres > 0) {
            BSTNode* newnode = _make_node(data);
            newnode->parent = parent;
            parent->left = newnode;
            tree->size += 1;
        } else if (cmpres == 0) {
            returned = node->data;
            node->data = data;
        }
    }
    return returned;
}

void* bst_find(BST* tree, void* data) {
    void* returned = NULL;
    if (tree->root != NULL) {
        BSTNode* node = tree->root;
        int cmpres = 0;
        while (node != NULL) {
            cmpres = (tree->cmp)(node->data, data);
            if (cmpres < 0) {
                node = node->right;
            } else if (cmpres > 0) {
                node = node->left;
            } else {
                returned = node->data;
                break;
            }
        }
    }
    return returned;
}

void* bst_delete(BST* tree, void* data) {
    void* returned = NULL;
    if (tree->root != NULL) {
        BSTNode* node = tree->root;
        int cmpres = 0;
        while (node != NULL) {
            cmpres = (tree->cmp)(node->data, data);
            if (cmpres < 0) {
                node = node->right;
            } else if (cmpres > 0) {
                node = node->left;
            } else {
                returned = node->data;
                break;
            }
        }
        if (node != NULL) {
            _remove_node(tree, node);
            _free_node(node);
            tree->size -= 1;
        }
    }
    return returned;
}

void bst_clear(BST* tree) {
    BSTNode* min = _sub_min(tree->root);
    BSTNode* parent = (BSTNode*)(min->parent);
    while (tree->root != NULL) {
        if (min->right == NULL) {
            _remove_node(tree, min);
            _free_node(min);
            min = parent;
            if (min != NULL) {
                parent = (BSTNode*)(min->parent);
            } else {
                parent = NULL;
            }
        } else {
            min = _sub_min((BSTNode*)(min->right));
            parent = (BSTNode*)(min->parent);
        }
    }
    tree->size = 0;
}

void bst_destroy(BST* tree) {
    bst_clear(tree);
    _free_tree(tree);
}


void bst_foreach(BST* tree,
        void (*foreach_func)(void* data, void* extra_data),
        void* extra_data) {
    if (tree->root != NULL) {
        BSTNode* node = _sub_min(tree->root);
        while (node != NULL) {
            foreach_func(node->data, extra_data);
            node = _successor(node);
        }
    }
}


