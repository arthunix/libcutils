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

#include <sysinfoapi.h>
#include <BaseTsd.h>
#include <WinDef.h>
#include <WinNT.h>

#if defined(LIBCUTILS_EXPORTS)
#define LIBCUTILS_API __declspec(dllexport)
#else
#define LIBCUTILS_API __declspec(dllimport)
#endif

#elif defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)

#include <sys/time.h>

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

    LIBCUTILS_API typedef struct listnode queuenode;
    LIBCUTILS_API typedef struct listnode QueueNode;
    LIBCUTILS_API typedef struct listnode QUEUENODE;
    LIBCUTILS_API typedef struct listnodeptr queuenodeptr;
    LIBCUTILS_API typedef struct listnodeptr QueueNodePtr;
    LIBCUTILS_API typedef struct listnodeptr QUEUENODEPTR;

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

    LIBCUTILS_API typedef struct doublelinkedlist circularlist;
    LIBCUTILS_API typedef struct doublelinkedlist CircularList;
    LIBCUTILS_API typedef struct doublelinkedlist CIRCULARLIST;
    LIBCUTILS_API typedef struct doublelinkedlist ringbuffer;
    LIBCUTILS_API typedef struct doublelinkedlist RingBuffer;
    LIBCUTILS_API typedef struct doublelinkedlist RINGBUFFER;
    LIBCUTILS_API typedef struct doublelinkedlist queue;
    LIBCUTILS_API typedef struct doublelinkedlist Queue;
    LIBCUTILS_API typedef struct doublelinkedlist QUEUE;

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
    } Rbrb_tree, RBrb_tree, rbtree;

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

    LIBCUTILS_API doublelinkedlist* double_linked_list_create(int (*_cmpfun)(const void*, const void*), void (*_destroydata)(void*), void (*_printdata)(const void*));
    LIBCUTILS_API void double_linked_list_destroy(doublelinkedlist* double_linked_list);
    LIBCUTILS_API listnode* double_linked_list_insert_at_index(doublelinkedlist* double_linked_list, const void* value, unsigned int position);
    LIBCUTILS_API void double_linked_list_pop_at_index(doublelinkedlist* double_linked_list, unsigned int position);
    LIBCUTILS_API listnode* double_linked_list_insert_back(doublelinkedlist* double_linked_list, const void* value);
    LIBCUTILS_API listnode* double_linked_list_insert_front(doublelinkedlist* double_linked_list, const void* value);
    LIBCUTILS_API void double_linked_list_pop_back(doublelinkedlist* double_linked_list);
    LIBCUTILS_API void double_linked_list_pop_front(doublelinkedlist* double_linked_list);
    LIBCUTILS_API listnode* double_linked_list_insert_back_sorted(doublelinkedlist* double_linked_list, const void* value);
    LIBCUTILS_API listnode* double_linked_list_insert_front_sorted(doublelinkedlist* double_linked_list, const void* value);
    LIBCUTILS_API void double_linked_list_sort(doublelinkedlist* double_linked_list);
    LIBCUTILS_API listnode double_linked_list_front(doublelinkedlist* double_linked_list);
    LIBCUTILS_API listnode double_linked_list_back(doublelinkedlist* double_linked_list);
    LIBCUTILS_API listnode double_linked_list_retrieve(doublelinkedlist* double_linked_list, unsigned int position);
    LIBCUTILS_API void double_linked_list_for_each(void (*operation)(listnode a));

    LIBCUTILS_API circularlist* circular_linked_list_create(int (*_cmpfun)(const void*, const void*), void (*_destroydata)(void*), void (*_printdata)(const void*));
    LIBCUTILS_API void circular_list_destroy(circularlist* circular_list);
    LIBCUTILS_API listnode* circular_list_insert_at_index(circularlist* circular_list, const void* value, unsigned int position);
    LIBCUTILS_API void circular_list_pop_at_index(circularlist* circular_list, unsigned int position);
    LIBCUTILS_API listnode* circular_list_insert_back(circularlist* circular_list, const void* value);
    LIBCUTILS_API listnode* circular_list_insert_front(circularlist* circular_list, const void* value);
    LIBCUTILS_API void circular_list_pop_back(circularlist* circular_list);
    LIBCUTILS_API void circular_list_pop_front(circularlist* circular_list);
    LIBCUTILS_API listnode* circular_list_insert_back_sorted(circularlist* circular_list, const void* value);
    LIBCUTILS_API listnode* circular_list_insert_front_sorted(circularlist* circular_list, const void* value);
    LIBCUTILS_API void circular_list_sort(circularlist* circular_list);
    LIBCUTILS_API listnode circular_list_front(circularlist* circular_list);
    LIBCUTILS_API listnode circular_list_back(circularlist* circular_list);
    LIBCUTILS_API listnode circular_list_retrieve(circularlist* circular_list, unsigned int position);
    LIBCUTILS_API void circular_list_for_each(void (*operation)(listnode a));

    LIBCUTILS_API queue* queue_create(int (*_cmpfun)(const void*, const void*), void (*_destroydata)(void*), void (*_printdata)(const void*));
    LIBCUTILS_API void queue_destroy(queue* double_linked_list);
    LIBCUTILS_API void queue_push(queue* double_linked_list, const void* value);
    LIBCUTILS_API queuenode queue_pop(queue* double_linked_list);
    LIBCUTILS_API queuenode queue_retrieve_first(queue* double_linked_list);
    LIBCUTILS_API queuenode queue_retrieve_last(queue* double_linked_list);
    LIBCUTILS_API void queue_size(queue* double_linked_list);

    LIBCUTILS_API stack* stack_create(int (*_cmpfun)(const void*, const void*), void (*_destroydata)(void*), void (*_printdata)(const void*));
    LIBCUTILS_API void stack_destroy(stack* double_linked_list);
    LIBCUTILS_API void stack_push(stack* double_linked_list, const void* value);
    LIBCUTILS_API stacknode stack_pop(stack* double_linked_list);
    LIBCUTILS_API stacknode stack_top(stack* double_linked_list);
    LIBCUTILS_API void stack_size(stack* double_linked_list);

    LIBCUTILS_API rbtree* rbtree_create(int (*cmpfun)(const void*, const void*),void (*destroydata)(void*),void (*printdata)(const void*));
    LIBCUTILS_API void rbtree_destroy(rbtree* rb_tree);
    LIBCUTILS_API rbnode* rbtree_insert(rbtree* rb_tree, void*);
    LIBCUTILS_API void rbtree_delete(rbtree* rb_tree, rbnode* rb_node_to_remove);
    LIBCUTILS_API void rbtree_print_inorder(const rbtree* rb_tree);
    LIBCUTILS_API void rbtree_print_preorder(const rbtree* rb_tree);
    LIBCUTILS_API void rbtree_print_postorder(const rbtree* rb_tree);
    LIBCUTILS_API rbnode* rbtree_search(const rbtree* rb_tree, const void* data);
    LIBCUTILS_API doublelinkedlist* rbtree_search_array(const rbtree* rb_tree, const void* data);
    LIBCUTILS_API rbnode* rbtree_predecessor(const rbtree* rb_tree, const rbnode*);
    LIBCUTILS_API rbnode* rbtree_successor(const rbtree* rb_tree, const rbnode*);

    LIBCUTILS_API void* safe_malloc(size_t n, unsigned long line);

    #define malloc_v(n) safe_malloc(n, __LINE__)

    /*
    please declare the following variables and pass them as parameters:
    double how_much_time_taken; clock_t how_much_clock_taken;
    */
    #define log_cpu_time_taken(how_much_clock_taken, function, how_much_time_taken) {                       \
        how_much_clock_taken = clock();                                                                     \
        function;                                                                                           \
        how_much_clock_taken = clock() - how_much_clock_taken;                                              \
        how_much_time_taken = ((double)clock_var)/CLOCKS_PER_SEC;                                           \
    fprintf(stderr, "CPU time taken: %.5lf in %s at line %i\n", how_much_time_taken, #function, __LINE__);  \
    }

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)

    /*
    please declare the following variables and pass them as parameters:
    double how_much_time_taken; struct timeval time_val_beg, time_val_end; long how_much_time_sec, how_much_time_usec;
    */
    #define log_wall_time_taken(wall_time_var_beg, wall_time_var_end, function, time_taken) {                               \
        wall_time_var_beg = GetTickCount64();                                                                               \
        function;                                                                                                           \
        wall_time_var_end = GetTickCount64();                                                                               \
        time_taken = (wall_time_var_end - wall_time_var_beg)*1e-10;                                                         \                                                                 \
        fprintf(stderr, "Wall time taken: %.5lf sec in %s at line %i\n", time_taken, #function, __LINE__);                  \
    }

#elif defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)

    /*
    please declare the following variables and pass them as parameters:
    double how_much_time_taken; struct timeval time_val_beg, time_val_end; long how_much_time_sec, how_much_time_usec;
    */
    #define log_wall_time_taken(how_much_time_sec, how_much_time_usec, wall_time_var_beg, wall_time_var_end, function, time_taken) {    \
        gettimeofday(&wall_time_var_beg, 0);                                                                                            \
        function;                                                                                                                       \
        gettimeofday(&wall_time_var_end, 0);                                                                                            \
        how_much_time_sec = wall_time_var_end.tv_sec - wall_time_var_beg.tv_sec;                                                        \
        how_much_time_usec = wall_time_var_end.tv_usec - wall_time_var_beg.tv_usec;                                                     \
        time_taken = wall_var_sec + wall_var_usec*1e-10;                                                                                \
        fprintf(stderr, "Wall time taken: %.5lf sec in %s at line %i\n", time_taken, #function, __LINE__);                              \
    }

#endif

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
