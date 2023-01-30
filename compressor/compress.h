#ifndef _COMPRESS_H_
#define _COMPRESS_H_
#include "htnqueue.h"
#include <stdio.h>

void compress(
        FILE* istream,
        FILE* ostream,
        size_t fbos_buffer_sz,
        size_t* origin_szp,
        size_t* tree_szp,
        size_t* new_szp
        );

#endif
