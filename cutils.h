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
#ifndef __LIB_CUTILS_H
#define __LIB_CUTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
        struct listnode* pPrev;
        struct listnode* pNext;
        void* data;
    }listnode, ListNode, LISTNODE, * listnodeptr, * ListNodePtr, * LISTNODEPTR;

    LIBCUTILS_API typedef struct listproto {
        int  (*cmpfun)(const void* a, const void* b);
        void (*destroydata)(void* a);
        void (*printdata)(const void* a);
    }listproto, ListProto, LISTPROTO;

    LIBCUTILS_API typedef struct doublelinkedlist {
        listproto protofun;
        struct listnode* pHead;
        struct listnode* pTail;
        long long int size;
        char isItSorted;
    }doublelinkedlist, DoubleLinkedList, DOUBLELINKEDLIST;

    LIBCUTILS_API typedef struct circularlist {
        listproto protofun;
        struct listnode* pHead;
        struct listnode* pTail;
        long long int size;
        char isItSorted;
    } circularlist, CircularList, CIRCULARLIST, ringbuffer, RingBuffer, RINGBUFFER;

    LIBCUTILS_API typedef struct queue {
        listproto protofun;
        struct listnode* pHead;
        struct listnode* pTail;
        long long int size;
        char isItSorted;
    } queue, Queue, QUEUE;

    LIBCUTILS_API typedef struct RbNode {
        void* data;
        unsigned short int red;
        struct RbNode* left;
        struct RbNode* right;
        struct RbNode* parent;
    } RbNode, RBNODE, rbnode;

    LIBCUTILS_API typedef struct RbTree {
        int  (*cmpfun)(const void* a, const void* b);
        void (*destroydata)(void* a);
        void (*printdata)(const void* a);
        struct RbNode* root;
        struct RbNode* nil;
    } RbTree, RBTREE, rbtree;

    LIBCUTILS_API typedef struct stacknode {
        struct stacknode* up;
        struct stacknode* down;
        void* data;
    } stacknode, StackNode, STACKNODE, * stacknodeptr, * StackNodePtr, * STACKNODEPTR;

    LIBCUTILS_API typedef struct Stack {
        int  (*cmpfun)(const void* a, const void* b);
        void (*destroydata)(void* a);
        void (*printdata)(const void* a);
        struct stacknode* top;
        unsigned int size;
    }stack, Stack, STACK;

    LIBCUTILS_API unsigned int stack_size(const stack* stack_input);
    LIBCUTILS_API int stack_empty(const stack* stack_input);
    LIBCUTILS_API stack* stack_create(int (*_cmpfun)(const void*, const void*), void (*_destroydata)(void*), void (*_printdata)(const void*));
    LIBCUTILS_API void stack_destroy(stack* stack_input);
    LIBCUTILS_API stacknode* stack_top(stack* stack_input);
    LIBCUTILS_API void stack_push(stack* stack_input, void* new_inserted_data);
    LIBCUTILS_API void stack_pop(stack* stack_input);
    LIBCUTILS_API void stack_print(const stack* list_input);

    LIBCUTILS_API void* safe_malloc(size_t n, unsigned long line);

    #define malloc_v(n) safe_malloc(n, __LINE__)

    #define log_time_taken(clock_var, function, time_taken) {       \
        clock_var = clock();                                        \
        function;                                                   \
        clock_var = clock() - clock_var;                            \
        time_taken = ((double)t)/CLOCKS_PER_SEC;                    \
    }

    LIBCUTILS_API void print_array(
        void* data,
        size_t sizeOfTheType,
        size_t p_start,
        size_t p_numOfElements,
        void (*printfun)(const void*)
    );

#ifdef __cplusplus
}
#endif

#endif // !__LIB_CUTILS_H