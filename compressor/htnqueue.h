#ifndef _HTNQUEUE_H_
#define _HTNQUEUE_H_
#include "htnode.h"

void htnqueue_insert(HTNode** htnqueue, size_t* szp, HTNode* htnode);

HTNode* htnqueue_extract(HTNode** htnqueue, size_t* szp);

#endif


