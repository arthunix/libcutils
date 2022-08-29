/*
BSD 2-Clause License

Copyright (c) 2022, Arthur Eugenio Silverio
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
    struct listnode* pNext;
    struct listnode* pPrev;
    void* data;
}listnode, ListNode, LISTNODE, *listnodeptr, *ListNodePtr, *LISTNODEPTR;

LIBCUTILS_API typedef struct list
{
    int  (*cmpfun)(const void* a, const void* b);
    void (*destroydata)(void* a);
    void (*printdata)(const void* a);
    struct listnode* pHead;
    struct listnode* pTail;
    long long int size;
    char isItSorted;
}list, List, LIST;

LIBCUTILS_API unsigned int list_size(const list* list_input);

LIBCUTILS_API unsigned int list_empty(const list* list_input);

LIBCUTILS_API list* list_create(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
);

LIBCUTILS_API void list_destroy(list* list_input);

LIBCUTILS_API void list_push_front(list* list_input, void* new_value);

LIBCUTILS_API void list_pop_front(list* list_input);

LIBCUTILS_API void list_push_back(list* list_input, void* new_value);

LIBCUTILS_API void list_pop_back(list* list_input);

LIBCUTILS_API void list_insert_sorted(list* list_input);

LIBCUTILS_API void list_sort(list* list_input, void(*_sort)(const void*));

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