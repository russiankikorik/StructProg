#include "compress.h"
#include "bitio.h"

#include <stdlib.h>
#include <stdio.h>

size_t get_statistics(FILE* istream, size_t* stats) {
    int sym;
    size_t i;
    for(i = 0; (sym = fgetc(istream)) != EOF; i += 1) {
        stats[sym] += 1;
    }
    rewind(istream);
    return i;
}

void make_nodes(HTNode** htnlist, size_t* stats) {    
    for (int i = 0; i < 256; i += 1) {
        HTNode* htnode = init_htnode();
        htnode->is_leaf = 1;
        htnode->sym = i;
        htnode->mass = stats[i];
        htnode->p = NULL;
        htnode->l = NULL;
        htnode->r = NULL;
        htnlist[i] = htnode;
    }
}

HTNode* make_tree(HTNode** htnodes) {
    HTNode* htnqueue[256];
    size_t htnq_sz = 0;
    for (size_t i = 0; i < 256; i += 1) {
        if (htnodes[i]->mass != 0) {
            htnqueue_insert(htnqueue, &htnq_sz, htnodes[i]);
        }
    }
    HTNode* nodel;
    HTNode* noder;
    HTNode* nodep;
    while (htnq_sz != 1) {
        nodel = htnqueue_extract(htnqueue, &htnq_sz);
        noder = htnqueue_extract(htnqueue, &htnq_sz);
        nodep = init_htnode();
        nodel->p = nodep;
        noder->p = nodep;
        nodep->is_leaf = 0;
        nodep->p = NULL;
        nodep->l = nodel;
        nodep->r = noder;
        nodep->mass = nodel->mass + noder->mass;
        htnqueue_insert(htnqueue, &htnq_sz, nodep);
    }
    return htnqueue[0];
}

void write_symbol_count(FILE* ostream, size_t count) {
    fwrite(&count, sizeof(size_t), 1, ostream);
}

void write_tree(FBOstream* fbostream, HTNode* node, size_t* szp) {
    if (node->is_leaf == 1) {
        fwrite_bit(fbostream, 1);
        *szp += 1;
        unsigned char sym = node->sym;
        int bit;
        for (int i = 7; i >= 0; i -= 1) {
            bit = (sym >> i) & 1;
            fwrite_bit(fbostream, bit);
            *szp += 1;
        }
    } else {
        fwrite_bit(fbostream, 0);
        *szp += 1;
        write_tree(fbostream, (HTNode*)(node->l), szp);
        write_tree(fbostream, (HTNode*)(node->r), szp);
    }
}

size_t write_compressed_data(
        FBOstream* fbostream,
        FILE* istream,
        HTNode** nodes
        ) {
    size_t size = 0;
    int sym;
    while ((sym = fgetc(istream)) != EOF ) {
        HTNode* node = nodes[sym];
        HTNode* parent = node->p;
        int i;
        char buf[256];
        for (i = 0; parent != NULL; i += 1) {
            if((HTNode*)(parent->l) == node) {
                buf[i] = 0;
            } else {
                buf[i] = 1;
            }
            node = parent;
            parent = node->p;
        }
        if (i == 0) {
            fwrite_bit(fbostream, 0);
        }
        int j;
        for (j = i - 1; j >= 0; j -= 1) { 
            fwrite_bit(fbostream, buf[j]);
            size += 1;
        }
    }
    flush_bits(fbostream);
    return size;
}

void compress(
        FILE* istream,
        FILE* ostream,
        size_t fbos_buffer_sz,
        size_t* origin_szp,
        size_t* tree_szp,
        size_t* new_szp
        ) {
    FBOstream* fbostream = init_fbostream(ostream, fbos_buffer_sz);
    size_t stats[256];
    for (size_t i = 0; i < 256; i += 1) {
        stats[i] = 0;
    }
    HTNode* htnlist[256];
    *origin_szp = get_statistics(istream, stats);
    make_nodes(htnlist, stats);
    HTNode* root = make_tree(htnlist);
    write_symbol_count(ostream, *origin_szp);
    write_tree(fbostream, root, tree_szp);
    size_t compressed_bits = write_compressed_data(fbostream, istream, htnlist);
    *new_szp = sizeof(size_t) + 
        ((*tree_szp + compressed_bits) / (8 * fbos_buffer_sz) + 1) * fbos_buffer_sz;
    destroy_fbostream(fbostream);
    destroy_htree(root);
}
