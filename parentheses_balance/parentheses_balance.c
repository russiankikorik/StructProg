#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_parentheses(char expression[], char parentheses[]);

int is_parentheses(char sym, char parentheses[]);

int is_opening(char sym, char parentheses[]);

int is_pair(char open, char close, char parentheses[]);

int main() {
    char parentheses[] = "()<>[]{}ab";
    char expression[] = "()<a{ab}b>[]";
    int check = check_parentheses(expression, parentheses);
    printf("%d\n", check);
}

int check_parentheses(char expression[], char parentheses[]) {
    int length = strlen(expression);
    char* stack = malloc(length);
    char* top = stack;
    int is_correct = 1;
    for (int i = 0; i < length; i += 1) {
        char sym = expression[i];
        if (is_parentheses(sym, parentheses)) {
            if (is_opening(sym, parentheses)) {
                *top = sym;
                top += 1;
            } else {
                if (top == stack) {
                    is_correct = 0;
                    break;
                }
                if (is_pair(*(top - 1), sym, parentheses)) {
                    top -= 1;
                } else {
                    is_correct = 0;
                    break;
                }
            }
        }
    }
    if (top != stack) {
        is_correct = 0;
    }
    free(stack);
    return is_correct;                    
}

int is_parentheses(char sym, char parentheses[]) {
    int is = 0;
    if (strchr(parentheses, sym) != NULL) {
        is = 1;
    }
    return is;
}

int is_opening(char sym, char parentheses[]) {
    int is = 1;
    int ind = strchr(parentheses, sym) - parentheses;
    if (ind % 2 == 1) {
        is = 0;
    }
    return is;
}

int is_pair(char open, char close, char parentheses[]) {
    int is = 1;
    if (! is_opening(open, parentheses)) {
        is = 0;
    } else {
        int delta = strchr(parentheses, close) - strchr(parentheses, open);
        if (delta != 1) {
            is = 0;
        }
    }
    return is;
}
















