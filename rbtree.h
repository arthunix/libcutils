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
#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

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

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

LIBCUTILS_API typedef struct RbNode{
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

LIBCUTILS_API rbtree* rbtree_create(
    int (*cmpfun)(const void*, const void*),
    void (*destroydata)(void*),
    void (*printdata)(const void*)
);

LIBCUTILS_API void rbtree_destroy(rbtree* tree);

LIBCUTILS_API rbnode* rbtree_insert(rbtree* tree, void*);

LIBCUTILS_API void rbtree_delete(rbtree* tree, rbnode*);

LIBCUTILS_API void rbtree_print_inorder(const rbtree* tree);

LIBCUTILS_API void rbtree_print_preorder(const rbtree* tree);

LIBCUTILS_API void rbtree_print_postorder(const rbtree* tree);

LIBCUTILS_API rbnode* rbtree_search(const rbtree* tree, const void* data);

LIBCUTILS_API list* rbtree_search_array(const rbtree* tree, const void* data);

LIBCUTILS_API rbnode* rbtree_predecessor(const rbtree* tree, const rbnode*);

LIBCUTILS_API rbnode* rbtree_successor(const rbtree* tree, const rbnode*);

#ifdef __cplusplus
}
#endif

#endif // !RED_BLACK_TREE_H
