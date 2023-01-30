#include "htnode.h"
#include <stdlib.h>

HTNode* init_htnode(void) {
    HTNode* htnode = malloc(sizeof(HTNode));
    return htnode;
}

void destroy_htnode(HTNode* htnode) {
    free(htnode);
}

void destroy_htree(HTNode* root) {
    HTNode* l = root->l;
    HTNode* r = root->r;
    destroy_htnode(root);
    if (l != NULL) {
        destroy_htree(l);
    }
    if (r != NULL) {
        destroy_htree(r);
    }
}
