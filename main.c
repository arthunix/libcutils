#include <stdio.h>
#include <stdlib.h>

#include "cutils.h"

void int_destroy(void* a);
int int_cmp(const void* a, const void* b);
void int_print(const void* a);

int int_test1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int int_test2[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
int int_test3[10] = { 5, 3, 8, 2, 1, 7, 0, 6, 4, 9 };

int main()
{
    printf("These are the tests for LIBCUTILS - Hello World!\n");

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