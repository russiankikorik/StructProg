#include "decompress.h"
#include "compress.h"
#include <stdio.h>
#include <string.h>

const char help[] = "This is simple data compressing utility.\n\
It is based on Huffman prefix code tree.\n\n\
To compress data pass arguments in this order:\n\
1) -c or -compress key\n\
2) name of the input file to be compressed\n\
3) name of the compressed output file\n\n\
To decompress data pass arguments in this order:\n\
1) -d or -decompress key\n\
2) name of the input file to be decompressed\n\
3) name of the decompressed output file\n\n\
Limitations:\n\
1) Same names of input and output files are not allowed.\n\
2) Utility overwrites existing file if its name is passed \
as output argument.\n";

void print_stats(size_t origin_sz, size_t tree_sz, size_t new_sz) {
    printf("tree size %ld bits\n", tree_sz);
    printf("origin size %ld bytes\n", origin_sz);
    printf("new size %ld bytes\n", new_sz);
    double ratio = (double)new_sz / (double)origin_sz;
    printf("compression ratio %.4lf\n", ratio);
}
  

int main(int argc, char** argv) {
    switch (argc) {
        case 1:
            printf("no arguments given, run with -h or -help for help\n");
            break;
        case 2:
            if (0 == strcmp(argv[1], "-h") || 0 == strcmp(argv[1], "-help")) {
                printf(help);
            } else {
                printf("too few arguments given, run with -h or -help for help\n");
            }
            break;
        case 3:
            printf("too few arguments given, run with -h or -help for help\n");
            break;
        case 4:
            if (0 == strcmp(argv[2], argv[3])) {
                printf("Same names of input and output files are not allowed\n");
            } else if (0 == strcmp(argv[1], "-c") || 0 == strcmp(argv[1], "-compress")) {
                FILE* input = fopen(argv[2], "rb");
                if (input == NULL) {
                    printf("error while opening input file\n");
                    break;
                }
                FILE* output = fopen(argv[3], "wb");
                if (output == NULL) {
                    printf("error while opening output file\n");
                    fclose(input);
                }
                if (input != NULL && output != NULL) {
                    size_t origin_sz, tree_sz, new_sz;
                    tree_sz = 0;
                    compress(input, output, 1024, &origin_sz, &tree_sz, &new_sz);
                    print_stats(origin_sz, tree_sz, new_sz);
                    if (EOF == fclose(input)) {
                        printf("error on closing input file\n");
                    }
                    if (EOF == fclose(output)) {
                        printf("error on closing output file\n");
                    }
                }
            } else if (0 == strcmp(argv[1], "-d") || 0 == strcmp(argv[1], "-decompress")) {
                FILE* input = fopen(argv[2], "rb");
                if (input == NULL) {
                    printf("error while opening input file\n");
                    break;
                }
                FILE* output = fopen(argv[3], "wb");
                if (output == NULL) {
                    printf("error while opening output file\n");
                    fclose(input);
                }
                if (input != NULL && output != NULL) {
                    decompress(input, output, 1024);
                    if (EOF == fclose(input)) {
                        printf("error on closing input file\n");
                    }
                    if (EOF == fclose(output)) {
                        printf("error on closing output file\n");
                    }
                }
            } else {
                printf("wrong key given, run with -h or -help for help\n");
            }
            break;
        default:
            printf("too many arguments given, run with -h or -help for help\n");
            break;
    }
    return 0;
}
