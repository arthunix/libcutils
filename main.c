#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "rbtree.h"
#include "common.h"
#include "stack.h"

void int_destroy(void* a);
int int_cmp(const void* a, const void* b);
void int_print(const void* a);

int int_test1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int int_test2[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
int int_test3[10] = { 5, 3, 8, 2, 1, 7, 0, 6, 4, 9 };

int main()
{
    printf("These are the tests for LIBCUTILS - Hello World!\n");

    list *list1, *list2;
    stack *stack1, *stack2;
    rbtree *tree1, *tree2;

    list1 = list_contructor(int_cmp, int_destroy, int_print);
    list2 = list_contructor(int_cmp, int_destroy, int_print);
    stack1 = stack_contructor(int_cmp, int_destroy, int_print);
    stack2 = stack_contructor(int_cmp, int_destroy, int_print);
    tree1 = rbtree_create(int_cmp, int_destroy, int_print);
    tree2 = rbtree_create(int_cmp, int_destroy, int_print);

    for (int i = 0; i < 10; i++) {
        int *pNewInt;
        pNewInt = (int*)malloc_v(sizeof(int*));
        *pNewInt = int_test1[i];
        list_push_back(list1, pNewInt);
    }
    
    list_print(list1, 0, list_size(list1));

    list_destructor(list1);
    list_destructor(list2);
    stack_destructor(stack1);
    stack_destructor(stack2);
    rbtree_destroy(tree1);
    rbtree_destroy(tree2);

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