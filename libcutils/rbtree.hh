#pragma once
#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#ifdef LIBCUTILS_EXPORTS
#define LIBCUTILS_API __declspec(dllexport)
#else
#define LIBCUTILS_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern "C" LIBCUTILS_API typedef struct RbNode{
    void* data;
    unsigned short int red;
    struct RbNode* left;
    struct RbNode* right;
    struct RbNode* parent;
} RbNode, RBNODE, rbnode;

extern "C" LIBCUTILS_API typedef struct RbTree {
    int  (*cmpfun)(const void* a, const void* b);
    void (*destroydata)(void* a);
    void (*printdata)(const void* a);
    struct RbNode* root;
    struct RbNode* nil;
} RbTree, RBTREE, rbtree;

extern "C" LIBCUTILS_API rbtree* rbtree_create(
    int (*cmpfun)(const void*, const void*),
    void (*destroydata)(void*),
    void (*printdata)(const void*)
);

extern "C" LIBCUTILS_API void rbtree_destroy(rbtree* tree);

extern "C" LIBCUTILS_API rbnode* rbtree_insert(rbtree* tree, void*);

extern "C" LIBCUTILS_API void rbtree_delete(rbtree* tree, rbnode*);

extern "C" LIBCUTILS_API void rbtree_print_inorder(const rbtree* tree);

extern "C" LIBCUTILS_API void rbtree_print_preorder(const rbtree* tree);

extern "C" LIBCUTILS_API void rbtree_print_postorder(const rbtree* tree);

extern "C" LIBCUTILS_API rbnode* rbtree_search(const rbtree* tree, const void* data);

extern "C" LIBCUTILS_API rbnode* rbtree_predecessor(const rbtree* tree, const rbnode*);

extern "C" LIBCUTILS_API rbnode* rbtree_successor(const rbtree* tree, const rbnode*);

#ifdef __cplusplus
}
#endif

#endif // !RED_BLACK_TREE_H
