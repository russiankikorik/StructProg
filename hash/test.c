#include <assert.h>
#include <stdio.h>
#include "hlist.h"

void printer(char* key, void* data) {
    printf("%s, %d\n", key, *((int*)data));
}

int main() {
    HLnode* list = NULL;
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    list = hlist_insert(list, "kek", &a, NULL);
    list = hlist_insert(list, "lol", &b, NULL);
    list = hlist_insert(list, "lulz", &c, NULL);
    hlist_foreach(list, printer);
    assert(*((int*)hlist_get(list, "kek")) == 0);
    assert(*((int*)hlist_get(list, "lol")) == 1);
    assert(*((int*)hlist_get(list, "lulz")) == 2);
    list = hlist_insert(list, "lulz", &d, NULL);
    hlist_foreach(list, printer);
    list = hlist_delete(list, "kek", NULL);
    list = hlist_delete(list, "lol", NULL);
    list = hlist_delete(list, "lulz", NULL);
    return 0;
}
