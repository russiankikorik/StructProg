#ifndef _DECOMPRESS_H_
#define _DECOMPRESS_H_
#include "htnqueue.h"
#include <stdio.h>

void decompress(
        FILE* istream,
        FILE* ostream,
        size_t fbis_buffer_sz
        );

#endif
