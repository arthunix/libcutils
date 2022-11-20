# LIBCUTILS
This library include some sort of util code for dealing with C programs

### About Generic Utils Code:

```C
mytypeptr* mymemptr = (mytypeptr*)malloc_v(sizeof(mytypeptr))

double how_much_time_taken; clock_t how_much_clock_taken;
log_cpu_time_taken(how_much_clock_taken, function, how_much_time_taken);

//#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
double how_much_time_taken; struct timeval time_val_beg, time_val_end; long how_much_time_sec, how_much_time_usec;
log_wall_time_taken(wall_time_var_beg, wall_time_var_end, function, time_taken);

//#if defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)
double how_much_time_taken; struct timeval time_val_beg, time_val_end; long how_much_time_sec, how_much_time_usec;
log_wall_time_taken(how_much_time_sec, how_much_time_usec, wall_time_var_beg, wall_time_var_end, function, time_taken);

mytype array[10];
//print_array(void* data,size_t sizeOfTheType,size_t p_start, size_t p_numOfElements,void (*printfun)(const void*)
print_array((void*)array, sizeof(mytype), 0 /* if start from beggining */, sizeof(array)/sizeof(array[0]) /* elements to print */, user_defined_print_function);
```

### How to Define Helper Functions:
```C

/* You can define in the way you want */

void int_destroy(void* a) {
    free((int*)a);
}

int* int_allocate(void* a) {
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

```

### About Red-Black Trees:

```C
rbtree* my_tree;
my_tree = rbtree_create(my_type_compare_helper, my_type_destroy_helper, my_type_allocate_helper, my_type_print_helper);
```

### About Circular/Linked/Queue/Stack Lists:

```C
doublelinkedlist*   my_doublelinkedlist;
circularlist*       my_circularlist;
queue*              my_queue;
stack*              my_stack;

my_doublelinkedlist = double_linked_list_create(my_type_compare_helper, my_type_destroy_helper, my_type_allocate_helper, my_type_print_helper);
my_circularlist   = circular_linked_list_create(my_type_compare_helper, my_type_destroy_helper, my_type_allocate_helper, my_type_print_helper);
my_queue            = queue_create(my_type_compare_helper, my_type_destroy_helper, my_type_allocate_helper, my_type_print_helper);
my_stack            = stack_create(my_type_compare_helper, my_type_destroy_helper, my_type_allocate_helper, my_type_print_helper);
```


TODO:
1) I need a strong sort of testing code
2) Organize, refactor and make my code about gaphs good to push
3) Organize, refactor and make my code about hash tables good to push
4) Organize, refactor and make my code about maps good to push
