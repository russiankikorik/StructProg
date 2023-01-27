#include "htnqueue.h"

static size_t parent(size_t i) {
    return (i - 1) / 2;
}

static size_t left(size_t i) {
    return 2 * i + 1;
}

static size_t right(size_t i) {
    return 2 * i + 2;
}

static void swap(HTNode** htnqueue, size_t i, size_t j) {
    HTNode* buf = htnqueue[i];
    htnqueue[i] = htnqueue[j];
    htnqueue[j] = buf;
}

static void sink(HTNode** htnqueue, size_t sz, size_t i) {
    if (i < sz) {
        size_t l = left(i);
        size_t r = right(i);
        size_t min;
        if (l < sz && htnqueue[l]->mass < htnqueue[i]->mass) {
            min = l;
        } else {
            min = i;
        }
        if (r < sz && htnqueue[r]->mass < htnqueue[min]->mass) {
            min = r;
        }
        if (min != i) {
            swap(htnqueue, i, min);
            sink(htnqueue, sz, min);
        }
    }
}

static void surface(HTNode** htnqueue, size_t sz, size_t i) {
    if (i < sz && i > 0) {
        if (htnqueue[parent(i)]->mass > htnqueue[i]->mass) {
            swap(htnqueue, i, parent(i));
            surface(htnqueue, sz, parent(i));
        }
    }
}

void htnqueue_insert(HTNode** htnqueue, size_t* szp, HTNode* htnode) {
    htnqueue[*szp] = htnode;
    *szp += 1;
    surface(htnqueue, *szp, *szp - 1);
}

HTNode* htnqueue_extract(HTNode** htnqueue, size_t* szp) {
    HTNode* buf = htnqueue[0];
    swap(htnqueue, 0, *szp - 1);
    *szp -= 1;
    sink(htnqueue, *szp, 0);
    return buf;
}
