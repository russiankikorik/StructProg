#ifndef _HTNODE_H_
#define _HTNODE_H_
#include <stddef.h>

typedef struct tHTNode {
    char is_leaf;
    unsigned char sym;
    size_t mass;
    void* p;
    void* l;
    void* r;
} HTNode;

HTNode* init_htnode(void); 

void destroy_htnode(HTNode* htnode);

void destroy_htree(HTNode* root);

#endif
