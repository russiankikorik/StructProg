#include "bitio.h"

FBOstream* init_fbostream(FILE* ostream, size_t buffer_size) {
    FBOstream* fbostream = malloc(sizeof(FBOstream));
    fbostream->ostream = ostream;
    fbostream->buffer_size = buffer_size;
    fbostream->buffer = malloc(buffer_size);
    if (fbostream->buffer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    for (size_t i = 0; i < buffer_size; i += 1) {
        (fbostream->buffer)[i] = 0;
    }
    fbostream->carriage = 0;
    return fbostream;
}

void fwrite_bit(FBOstream* fbostream, int bit) {
    bit &= 1;
    size_t byte_offset = fbostream->carriage / 8;
    size_t bit_offset = fbostream->carriage % 8;
    char ready_bit = ((char*)(&bit))[0] << (7 - bit_offset);
    (fbostream->buffer)[byte_offset] |= ready_bit;
    fbostream->carriage += 1;
    if (fbostream->carriage / 8 == fbostream->buffer_size) {
        int bytes_written = fwrite(
                fbostream->buffer,
                1,
                fbostream->buffer_size,
                fbostream->ostream
                );
        if (bytes_written != fbostream->buffer_size) {
            fprintf(stderr, "error while writing to file\n");
            exit(1);
        }
        fbostream->carriage = 0;
        for (int i = 0; i < fbostream->buffer_size; i += 1) {
            (fbostream->buffer)[i] = 0;
        }
    }
}

int flush_bits(FBOstream* fbostream) {
    size_t byte_offset = fbostream->carriage / 8;
    size_t bit_offset = fbostream->carriage % 8;
    int bytes_written = fwrite(
            fbostream->buffer,
            1,
            byte_offset,
            fbostream->ostream
            );
    if (bytes_written != byte_offset) {
        fprintf(stderr, "Error while writing to file\n");
        exit(1);
    }
    int trailing_bits = 0;
    if (bit_offset != 0) {
        trailing_bits = 8 - bit_offset;
        char byte = (fbostream->buffer)[byte_offset] & (0xFF << trailing_bits);
        int bytes_written = fwrite(
            &byte,
            1,
            1,
            fbostream->ostream
            );
        if (bytes_written != 1) {
            fprintf(stderr, "Error while writing to file\n");
        }
    }
    fbostream->carriage = 0;
    return trailing_bits;
}

void destroy_fbostream(FBOstream* fbostream) {
    free(fbostream->buffer);
    free(fbostream);
}

FBIstream* init_fbistream(FILE* istream, size_t buffer_size) {
    FBIstream* fbistream = malloc(sizeof(FBIstream));
    fbistream->istream = istream;
    fbistream->buffer_size = buffer_size;
    fbistream->buffer = malloc(buffer_size);
    if (fbistream->buffer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    for (size_t i = 0; i < buffer_size; i += 1) {
        (fbistream->buffer)[i] = 0;
    }
    fbistream->carriage = 0;
    fbistream->byte_count = fread(fbistream->buffer, 1, buffer_size, istream);
    if (fbistream->byte_count != buffer_size) {
        if (!feof(istream)) {
            fprintf(stderr, "Error while reading from file");
            exit(1);
        }
    }
    return fbistream;
}

int fread_bit(FBIstream* fbistream) {
    int bit;
    if (fbistream->carriage / 8 >= fbistream->byte_count) {
        bit = -1;
    } else {
        int byte_offset = fbistream->carriage / 8;
        int bit_offset = fbistream->carriage % 8;
        char byte = (fbistream->buffer)[byte_offset];
        bit = (byte >> (7 - bit_offset)) & 1;
        fbistream->carriage += 1;
    }
    if (fbistream->carriage / 8 == fbistream->buffer_size) {
        fbistream->carriage = 0;
        fbistream->byte_count = fread(
                fbistream->buffer,
                1,
                fbistream->buffer_size,
                fbistream->istream);
        if (fbistream->byte_count != fbistream->buffer_size) {
            if (!feof(fbistream->istream)) {
                fprintf(stderr, "Error while reading from file");
                exit(1);
            }
        }
    }
    return bit;
}

void destroy_fbistream(FBIstream* fbistream) {
    free(fbistream->buffer);
    free(fbistream);
}

    
