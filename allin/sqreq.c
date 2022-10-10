#include "stdio.h"
#include "math.h"

void solve(float, float, float);

float input(const char*);

int main(void){
    solve(
            input("A: "),
            input("B: "),
            input("C: ")
         );
    return 0;
}

float input(const char* s) {
    printf("%s", s);
    float x;
    scanf("%f", &x);
    return x;
}


void solve(float a, float b, float c) {
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("All zeros\n");
            } else {
                printf("C != zero\n");
            }
        } else {
           printf("Linear, x = %.3f\n", (-c/b));
       }
    } else {
        float d = b * b - 4 * a * c;
        if (d < 0) {
            printf("No real roots\n");
        }
        else if (d == 0) {
            printf("Single root, x = %.3f\n", (-b / 2 / a));
        }
        else {
            float x1 = (-b - sqrt(d)) / 2 / a;
            float x2 = (-b + sqrt(d)) / 2 / a;
            printf("Two roots, x1 = %.3f, x2 = %.3f\n",x1, x2);
        }
    }
} 
