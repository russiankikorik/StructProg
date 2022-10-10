#include "stdio.h"

int day_number(int d, int m, int y);

int almost_valid(int d, int m, int y);

int main(void) {
    int d, m, y;
    scanf("%d %d %d", &d, &m, &y);
    if (almost_valid(d, m, y)) {
        printf("%d\n", day_number(d, m, y));
    } else {
        printf("-1\n");
    }
    return 0;
}

int almost_valid(int d, int m, int y) {
    int check = 1;
    if (d < 1 || m < 1 || m > 12 || y < 1) {
        check = 0;
    }
    return check;
}

int day_number(int d, int m, int y) {
    int a[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
        a[1] = 29;
    }
    int number = 0;
    for (int i = 0; i < m - 1; i += 1) {
        number += a[i];
    }
    number += d;
    if (a[m - 1] < d) {
      number = -1;
    }
    return number;
}
