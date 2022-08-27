#pragma once
#ifndef STACK_H
#define STACK_H

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
    #if defined(LIBCUTILS_EXPORTS)
        #define LIBCUTILS_API __declspec(dllexport)
    #else
        #define LIBCUTILS_API __declspec(dllimport)
    #endif
#elif defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)
    #if defined(LIBCUTILS_EXPORTS)
        #define LIBCUTILS_API __attribute__((visibility("default")))
    #else
        #define LIBCUTILS_API
    #endif
#else
    #define LIBCUTILS_API
    #pragma WARNING: Unknown dynamic link import/export semantics.
#endif


#ifdef __cplusplus
extern "C" {
#endif

LIBCUTILS_API typedef struct stacknode
{
    struct stacknode* up;
    struct stacknode* down;
    void* data;
} stacknode, StackNode, STACKNODE, *stacknodeptr, *StackNodePtr, *STACKNODEPTR;

LIBCUTILS_API typedef struct Stack
{
    int  (*cmpfun)(const void* a, const void* b);
    void (*destroydata)(void* a);
    void (*printdata)(const void* a);
    struct stacknode* top;
    unsigned int size;
}stack, Stack, STACK;

LIBCUTILS_API unsigned int stack_size(const stack* stack_input);

LIBCUTILS_API int stack_empty(const stack* stack_input);

LIBCUTILS_API stack* stack_contructor(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*));

LIBCUTILS_API void stack_destructor(stack* stack_input);

LIBCUTILS_API stacknode* stack_top(stack* stack_input);

LIBCUTILS_API void stack_push(stack* stack_input, void* new_inserted_data);

LIBCUTILS_API void stack_pop(stack* stack_input);

LIBCUTILS_API void stack_print(const stack* list_input);

#ifdef __cplusplus
}
#endif

#endif // !STACK_H