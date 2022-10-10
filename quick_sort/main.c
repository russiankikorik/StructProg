#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "quick_sort.h"

#define A 1000000

int cmp(void* a, void* b) {
    if (*((int*)a) < *((int*)b)) return -1;
    if (*((int*)a) == *((int*)b)) return 0;
    return 1;
}

int main() {
    int a[A];
    int b[A];
    int i;
    for (i = 0; i < A; i += 1) {
        a[i] = rand() % 1000;
    }
    for (i = 0; i < A; i += 1) {
        b[i] = i;
    }
    int c[10] = {72, 16, 421, 588, 52, 103, 937, 868, 315, 516};
    srand(time(NULL));
    for (i = 0; i < A; i += 1) {
        a[i] = rand() % 1000;
    }
    for (i = 0; i < 10; i += 1) {
        printf("%d ", c[i]);
    }
    printf("\n");
    quick_sort(c, 10, 4, cmp);
    for (i = 0; i < 10; i += 1) {
        printf("%d ", c[i]);
    }
    printf("\n");
    clock_t t0, t1, dt;
    for (i = 10; i <= A; i *= 10) {
        t0 = clock();
        quick_sort(a, i, sizeof(int), cmp);
        t1 = clock();
        dt = t1 - t0;
        printf("%10d  %.10f\n", i, (float)dt / (float)CLOCKS_PER_SEC);
    }
    for (i = 10; i <= A; i *= 10) {
        t0 = clock();
        quick_sort(b, i, sizeof(int), cmp);
        t1 = clock();
        dt = t1 - t0;
        printf("%10d  %.10f\n", i, (float)dt / (float)CLOCKS_PER_SEC);
    }
    for (i = 0; i < A; i += 1) {
        a[i] = rand() % 1000;
    }
    for (i = 10; i <= A; i *= 10) {
        t0 = clock();
        qsort(a, i, sizeof(int), cmp);
        t1 = clock();
        dt = t1 - t0;
        printf("%10d  %.10f\n", i, (float)dt / (float)CLOCKS_PER_SEC);
    }
    for (i = 10; i <= A; i *= 10) {
        t0 = clock();
        qsort(b, i, sizeof(int), cmp);
        t1 = clock();
        dt = t1 - t0;
        printf("%10d  %.10f\n", i, (float)dt / (float)CLOCKS_PER_SEC);
    }
    return 0;
}

