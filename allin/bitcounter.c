#include "stdio.h"

int bitcounter(int);

int main(void) {
    int a;
    scanf("%d", &a);
    printf("%d\n", bitcounter(a));
}

int bitcounter(int a) {
    int counter = 0;
    for (int i = 0; i < sizeof(a) * 8; i += 1) {
        if (a < 0) {
            counter += 1;
        }
        a <<= 1;
    }
    return counter;
}
