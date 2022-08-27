#pragma once
#ifndef LIST_H
#define LIST_H

#include <stddef.h>

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

LIBCUTILS_API typedef struct listnode {
    struct listnode* next;
    struct listnode* prev;
    void* data;
}listnode, ListNode, LISTNODE, *listnodeptr, *ListNodePtr, *LISTNODEPTR;

LIBCUTILS_API typedef struct list
{
    int  (*cmpfun)(const void* a, const void* b);
    void (*destroydata)(void* a);
    void (*printdata)(const void* a);
    struct listnode* head;
    struct listnode* tail;
    unsigned int size;
}list, List, LIST;

LIBCUTILS_API unsigned int list_size(const list* list_input);

LIBCUTILS_API unsigned int list_empty(const list* list_input);

LIBCUTILS_API list* list_contructor(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
);

LIBCUTILS_API void list_destructor(list* list_input);

LIBCUTILS_API void list_push_front(list* list_input, void* new_value);

LIBCUTILS_API void list_pop_front(list* list_input);

LIBCUTILS_API void list_push_back(list* list_input, void* new_value);

LIBCUTILS_API void list_pop_back(list* list_input);

LIBCUTILS_API void list_erase(list* list_input, unsigned int position);

LIBCUTILS_API void list_resize(list* list_input, unsigned int sz, void* value);

LIBCUTILS_API void list_clear(list* list_input);

LIBCUTILS_API listnode* list_front(const list* list_input);

LIBCUTILS_API listnode* list_back(const list* list_input);

LIBCUTILS_API void list_print(
    const list* list_input,
    size_t p_start,
    size_t p_numOfElements
);

#ifdef __cplusplus
}
#endif

#endif // !LIST_H