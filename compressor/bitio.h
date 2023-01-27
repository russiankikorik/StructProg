#ifndef _BITIO_H_
#define _BITIO_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct tFBOstream {
    FILE* ostream;
    char* buffer;
    size_t buffer_size;
    size_t carriage;
} FBOstream;

typedef struct tFBIstream {
    FILE* istream;
    char* buffer;
    size_t buffer_size;
    size_t byte_count;
    size_t carriage;
} FBIstream;

FBOstream* init_fbostream(FILE* ostream, size_t buffer_size);

void fwrite_bit(FBOstream* fbostream, int bit);

int flush_bits(FBOstream* fbostream);

void destroy_fbostream(FBOstream* fbostream);

FBIstream* init_fbistream(FILE* istream, size_t buffer_size);

int fread_bit(FBIstream* fbistream);

void destroy_fbistream(FBIstream* fbistream);

#endif



