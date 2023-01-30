#include "decompress.h"
#include "compress.h"
#include "stdio.h"

int main() {
    FILE* input = fopen("kek.pdf", "rb");
    FILE* output = fopen("kek.cmp", "wb");
    size_t origin_sz, tree_sz, new_sz;
    tree_sz = 0;
    compress(input, output, 1, &origin_sz, &tree_sz, &new_sz);
    fclose(input);
    fclose(output);
    input = fopen("kek.cmp", "rb");
    output = fopen("lol.pdf", "wb");
    decompress(input, output, 1);
    fclose(input);
    fclose(output);
    return 0;
}

