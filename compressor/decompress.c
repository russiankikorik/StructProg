#include "decompress.h"
#include "bitio.h"
#include <stdlib.h>

size_t read_symbol_count(FILE* istream) {
    size_t count;
    fread(&count, sizeof(size_t), 1, istream);
    return count;
}

HTNode* recreate_tree(FBIstream* fbistream) {
    int bit = fread_bit(fbistream);
    HTNode* htnode = init_htnode();
    if (bit == 1) {
        htnode->is_leaf = 1;
        htnode->l = NULL;
        htnode->r = NULL;
        unsigned char sym = 0;
        for (int i = 0; i < 8; i += 1) {
            bit = fread_bit(fbistream);
            sym |= bit << (7 - i);
        }
        htnode->sym = sym;
    } else {
        htnode->is_leaf = 0;
        htnode->l = recreate_tree(fbistream);
        htnode->r = recreate_tree(fbistream);
    }
    return htnode;
}

void read_compressed_data(
        FBIstream* fbistream,
        FILE* ostream,
        HTNode* htree_root,
        size_t symbol_count) {
    if (htree_root->is_leaf == 1) {
        fwrite(&(htree_root->sym), sizeof(char), symbol_count, ostream);
    } else {
        HTNode* htnode;
        int bit = 0;
        for (size_t i = 0; i < symbol_count; i += 1) {
            htnode = htree_root;
            while (htnode->is_leaf != 1) {
                bit = fread_bit(fbistream);
                if (bit == 0) {
                    htnode = htnode->l;
                } else {
                    htnode = htnode->r;
                }
            }
            fwrite(&(htnode->sym), sizeof(char), 1, ostream);
        }
    }
}

void decompress (
        FILE* istream,
        FILE* ostream,
        size_t fbis_buffer_sz
        ) {
    size_t symbol_count = read_symbol_count(istream);
    FBIstream* fbistream = init_fbistream(istream, fbis_buffer_sz);
    HTNode* htree_root = recreate_tree(fbistream);
    read_compressed_data(fbistream, ostream, htree_root, symbol_count);
    destroy_fbistream(fbistream);
    destroy_htree(htree_root);
}
