#include "htnode.h"
#include <stdlib.h>

HTNode* init_htnode(void) {
    HTNode* htnode = malloc(sizeof(HTNode));
    return htnode;
}

void destroy_htnode(HTNode* htnode) {
    free(htnode);
}
