#include <stdio.h>
#include <stdlib.h>

#include "rbtree.hh"
#include "common.hh"

void int_destroy(void* a);
int int_cmp(const void* a, const void* b);
void int_print(const void* a);

int main()
{
    printf("Hello World!\n");

    return 0;
}

void int_destroy(void* a) {
    free((int*)a);
}

int int_cmp(const void* a, const void* b) {
    if (*(int*)a < *(int*)b)
        return - 1;
    else if (*(int*)a > *(int*)b)
        return 1;
    else return 0;
}

void int_print(const void* a) {
    printf("%i", *(int*)a);
}