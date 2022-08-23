#pragma once
#ifndef LIST_H
#define LIST_H

#ifdef LIBCUTILS_EXPORTS
#define LIBCUTILS_API __declspec(dllexport)
#else
#define LIBCUTILS_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern "C" LIBCUTILS_API typedef struct listnode {
    struct listnode* next;
    struct listnode* prev;
    void* data;
}listnode, ListNode, LISTNODE, *listnodeptr, *ListNodePtr, *LISTNODEPTR;

extern "C" LIBCUTILS_API typedef struct list
{
    int  (*cmpfun)(const void* a, const void* b);
    void (*destroydata)(void* a);
    void (*printdata)(const void* a);
    struct listnode* head;
    struct listnode* tail;
    unsigned int size;
}list, List, LIST;

extern "C" LIBCUTILS_API unsigned int list_size(const list* list_input);

extern "C" LIBCUTILS_API unsigned int list_empty(const list* list_input);

extern "C" LIBCUTILS_API list* list_contructor(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
);

extern "C" LIBCUTILS_API void list_destructor(list* list_input);

extern "C" LIBCUTILS_API void list_push_front(list* list_input, void* new_value);

extern "C" LIBCUTILS_API void list_pop_front(list* list_input);

extern "C" LIBCUTILS_API void list_push_back(list* list_input, void* new_value);

extern "C" LIBCUTILS_API void list_pop_back(list* list_input);

extern "C" LIBCUTILS_API void list_erase(list* list_input, unsigned int position);

extern "C" LIBCUTILS_API void list_resize(list* list_input, unsigned int sz, void* value);

extern "C" LIBCUTILS_API void list_clear(list* list_input);

extern "C" LIBCUTILS_API listnode* list_front(const list* list_input);

extern "C" LIBCUTILS_API listnode* list_back(const list* list_input);

extern "C" LIBCUTILS_API void list_print(
    const list* list_input,
    size_t p_start,
    size_t p_numOfElements
);

#ifdef __cplusplus
}
#endif

#endif // !LIST_H