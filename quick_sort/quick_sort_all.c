#include <stdlib.h>
#include <time.h>

void _byteswap(void* p1, void* p2, size_t sz) {
    char* cp1 = (char*)p1;
    char* cp2 = (char*)p2;
    char buf;
    for (size_t i = 0; i < sz; i+= 1) {
        buf = cp1[i];
        cp1[i] = cp2[i];
        cp2[i] = buf;
    }
}

void _byteshuffle(void* arr, size_t n, size_t sz) {
    srand(time(NULL));
    char* a = (char*)arr;
    size_t j;
    for (size_t i = n - 1; i > 0; i -= 1) {
        j = rand() % (i + 1);
        _byteswap(a + j * sz, a + i * sz, sz);
    }
}

char* _split(char* start, char* end, size_t sz, int (*cmp)(void*, void*)){
   char* pi = start + sz;
   char* pj = end - sz;
   while(pi <= pj) {
       while(pi < end && cmp(pi, start) < 0) {
           pi += sz;
       }
       while(pj > start && cmp(pj, start) > 0) {
           pj -= sz;
       }
       if (pi >= pj) {
           break;
       } else {
           _byteswap(pi, pj, sz);
           pi += sz;
           pj -= sz;
       }
   }
   _byteswap(start, pj, sz);
   return pj;
}

void _quicksort(char* start, char* end, size_t sz, int (*cmp)(void*, void*)) {
    if (end - start > sz) {   
        char* pivot = _split(start, end, sz, cmp);
        _quicksort(start, pivot, sz, cmp);
        _quicksort(pivot + sz, end, sz, cmp);
    }
}

void quick_sort(void* arr, size_t n, size_t sz, int (*cmp)(void*, void*)) {
    if (n == 0 || sz == 0 || arr == NULL || cmp == NULL) {
        return;
    }
    //_byteshuffle(arr, n, sz);
    _quicksort((char*)arr, (char*)arr + n * sz, sz, cmp);
}
