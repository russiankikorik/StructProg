#include "stdio.h"

int main(void) {
    int a[100000];
    printf("Print number ");
    int n;
    scanf("%d", &n);
    printf("Print k ");
    int k;
    scanf("%d", &k);
    for (int i = 0; i < n; i += 1) {
        a[i] = i + 1;
    }
    int zc = 0;
    int i = 0;
    int j = 0;
    int m = 0;
    while (zc < n) {
        j = i % n;
        if (a[j] != 0) {
            m += 1;
            zc = 0;
            if (m % k == 0) {
                printf("%d out\n", a[j]);
                a[j] = 0;
            }
        } else {
            zc += 1;
        }
        i += 1;
    }
}

