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

#include <stdlib.h>

#include "cutils.h"

/*
TO DO:
- 1) I NEED A MORE STRONG NAMES AND COMMENTS
- 2) IF IT CAN BE MORE CLEAN, I THINK, LIKE OPENBSD CODE
*/


/*
* 
* THINK YOU NEED FUNCTIONS LIKE THAT

int int_cmp(const void* a, const void* b) {
    if (*(int*)a < *(int*)b)
        return - 1;
    else if (*(int*)a > *(int*)b)
        return 1;
    else return 0;
}

void int_destroy(void* a) {
    free((int*)a);
}

void int_print(const void* a) {
    printf("%i", *(int*)a);
}
*/

/// <summary>
/// This function take input of the functions will manipulate the data
/// that is of a generic castable void*, see above for an example
/// </summary>
/// <param name="_cmpfun">Function for comparition</param>
/// <param name="_destroydata">Function cast datatype and free it</param>
/// <param name="_printdata">Function print the datatype</param>
/// <returns>Return a pointer to the created node</returns>
rbtree* rbtree_create(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
) {
    rbtree* newTree;
    rbnode* temp;

    newTree = (rbtree*)malloc_v(sizeof(rbtree));

    newTree->cmpfun = _cmpfun;
    newTree->destroydata = _destroydata;
    newTree->printdata = _printdata;

    temp = newTree->nil = (rbnode*)malloc_v(sizeof(rbnode));
    temp->parent = temp->left = temp->right = temp;
    temp->red = 0;
    temp->data = 0;

    temp = newTree->root = (rbnode*)malloc_v(sizeof(rbnode));
    temp->parent = temp->left = temp->right = newTree->nil;
    temp->red = 0;
    temp->data = 0;
    return newTree;
}

void _rbtree_destroy(rbtree* tree, rbnode* x) {
    rbnode* nil = tree->nil;
    if (x != nil) {
        _rbtree_destroy(tree, x->left);
        _rbtree_destroy(tree, x->right);
        tree->destroydata(x->data);
        free(x);
    }
}

/// <summary>
/// Free all memory was allocated by the tree
/// </summary>
/// <param name="tree"></param>
void rbtree_destroy(rbtree* tree) {
    _rbtree_destroy(tree, tree->root->left);
    free(tree->root);
    free(tree->nil);
    free(tree);
}

/// <summary>
/// Rotates the node to the left.
/// </summary>
/// <param name="tree">is the tree that the node need to be rotated</param>
/// <param name="x">is the node will be rotated</param>
void left_rotate(rbtree* tree, rbnode* x) {
    rbnode* y;
    rbnode* nil = tree->nil;

    /* Turn y's left sub-tree into x's right sub-tree */
    y = x->right;
    x->right = y->left;
    /* y's new parent was x's parent */
    if (y->left != nil) {
        y->left->parent = x;
    }
    /* y's new parent was x's parent */
    y->parent = x->parent;
    if (x->parent != nil) {
        if (x == x->parent->left) {
            /* x was on the left of its parent */
            x->parent->left = y;
        }
        else {
            /* x must have been on the right */
            x->parent->right = y;
        }
    }
    else {
        tree->root = y;
    }
    /* Finally, put x on y's left */
    y->left = x;
    x->parent = y;
}

/// <summary>
/// Rotates the node to the right.
/// </summary>
/// <param name="tree">is the tree that the node need to be rotated</param>
/// <param name="x">is the node will be rotated</param>
void right_rotate(rbtree* tree, rbnode* y) {
    rbnode* x;
    rbnode* nil = tree->nil;

    /* Turn x's left sub-tree into y's right sub-tree */
    x = y->left;
    y->left = x->right;

    /* x's new parent was y's parent */
    if (nil != x->right) {
        x->right->parent = y;
    }
    /* x's new parent was y's parent */
    x->parent = y->parent;
    if (y->parent != nil) {
        if (y == y->parent->right) {
            /* y was on the right of its parent */
            y->parent->right = x;
        }
        else {
            /* y must have been on the left */
            y->parent->left = x;
        }
    }
    else {
        tree->root = x;
    }
    /* Finally, put y on x's right */
    x->right = y;
    y->parent = x;
}


void _rbtree_insert(rbtree* tree, rbnode* z) {
    rbnode* x;
    rbnode* y;
    rbnode* nil = tree->nil;

    z->left = z->right = nil;
    y = tree->root;
    x = tree->root->left;

    /* First we need to find the right position for the node */
    while (x != nil) {
        y = x;
        if (tree->cmpfun(x->data, z->data) > 0) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    z->parent = y;
    if ((y == tree->root) || 
        (tree->cmpfun(y->data, z->data) > 0)) {
        y->left = z;
    }
    else {
        y->right = z;
    }
}

/// <summary>
/// Inserts a node into a red black tree.
/// </summary>
/// <param name="tree"></param>
/// <param name="data"></param>
/// <returns>NULL on failure or the pointer to the newly added node otherwise</returns>
rbnode* rbtree_insert(rbtree* tree, void* data) {
    rbnode* y;
    rbnode* x;
    rbnode* newNode;

    x = (rbnode*)malloc_v(sizeof(rbnode));
    x->data = data;

    _rbtree_insert(tree, x);
    newNode = x;
    x->red = 1;
    while (x->parent->red) {
        if (x->parent == x->parent->parent->left) {

            y = x->parent->parent->right;
            if (y->red) {

                x->parent->red = 0;
                y->red = 0;
                x->parent->parent->red = 1;
                x = x->parent->parent;
            }
            else {

                if (x == x->parent->right) {
                    x = x->parent;
                    left_rotate(tree, x);
                }
                x->parent->red = 0;
                x->parent->parent->red = 1;
                right_rotate(tree, x->parent->parent);
            }
        }
        else {
            y = x->parent->parent->left;
            if (y->red) {
                x->parent->red = 0;
                y->red = 0;
                x->parent->parent->red = 1;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->left) {
                    x = x->parent;
                    right_rotate(tree, x);
                }
                x->parent->red = 0;
                x->parent->parent->red = 1;
                left_rotate(tree, x->parent->parent);
            }
        }
    }
    tree->root->left->red = 0;
    return newNode;
}

void _rbtree_print_node(const rbtree* tree, const rbnode* x) {
    rbnode* nil = tree->nil;
    rbnode* root = tree->root;

    printf("  key=");
    if (x == nil) {
        printf("error : NULL NODE");
        return;
    }
    else tree->printdata(x->data);

    printf("  l->key=");
    if (x->left == nil) printf("NULL");
    else tree->printdata(x->left->data);

    printf("  r->key=");
    if (x->right == nil) printf("NULL");
    else tree->printdata(x->right->data);

    printf("  p->key=");
    if (x->parent == root) printf("NULL");
    else tree->printdata(x->parent->data);

    printf("  red=%i\n", x->red);
}

void _rbtree_print_inorder(const rbtree* tree, const rbnode* x) {
    if (x != tree->nil) {
        _rbtree_print_inorder(tree, x->left);
        _rbtree_print_node(tree, x);
        _rbtree_print_inorder(tree, x->right);
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="tree"></param>
void rbtree_print_inorder(const rbtree* tree) {
    _rbtree_print_inorder(tree, tree->root->left);
}

void _rbtree_print_postorder(const rbtree* tree, const rbnode* x) {
    if (x != tree->nil) {
        _rbtree_print_postorder(tree, x->left);
        _rbtree_print_postorder(tree, x->right);
        _rbtree_print_node(tree, x);
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="tree"></param>
void rbtree_print_postorder(const rbtree* tree) {
    _rbtree_print_postorder(tree, tree->root->left);
}

void _rbtree_print_preorder(const rbtree* tree, const rbnode* x) {
    if (x != tree->nil) {
        _rbtree_print_node(tree, x);
        _rbtree_print_preorder(tree, x->left);
        _rbtree_print_preorder(tree, x->right);
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="tree"></param>
void rbtree_print_preorder(const rbtree* tree) {
    _rbtree_print_preorder(tree, tree->root->left);
}

/// <summary>
/// Searches the red black tree, returns the data if key is found or NULL otherwise.
/// </summary>
/// <param name="tree"></param>
/// <param name="data"></param>
/// <returns>NULL on failure or the pointer to the node otherwise</returns>
rbnode* rbtree_search(const rbtree* tree, const void* data) {
    rbnode* x = tree->root->left;
    rbnode* nil = tree->nil;

    if (x == nil)
        return nil;
    if (tree->cmpfun(x->data, data) == 0)
        return x;

    int cmp = tree->cmpfun(x->data, data);
    while (cmp != 0) {
        if (cmp > 0) {
            x = x->left;
        }
        else {
            x = x->right;
        }
        if (x == nil)
            return nil;
        cmp = tree->cmpfun(x->data, data);
    }
    return x;
}

/// <summary>
/// 
/// </summary>
/// <param name="tree"></param>
/// <param name="x"></param>
/// <returns>Return a pointer to the predecessor node</returns>
rbnode* rbtree_predecessor(const rbtree* tree, const rbnode* x) {
    rbnode* y;
    rbnode* nil = tree->nil;
    rbnode* root = tree->root;

    if (nil != (y = x->left)) {
        while (y->right != nil) {
            y = y->right;
        }
        return y;
    }
    else {
        y = x->parent;
        while (x == y->left) {
            if (y == root)
                return (nil);
            x = y;
            y = y->parent;
        }
        return y;
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="tree"></param>
/// <param name="x"></param>
/// <returns>Return a pointer to the successor node</returns>
rbnode* rbtree_successor(const rbtree* tree, const rbnode* x) {
    rbnode* y;
    rbnode* nil = tree->nil;
    rbnode* root = tree->root;

    if (nil != (y = x->right)) {
        while (y->left != nil) {
            y = y->left;
        }
        return y;
    }
    else {
        y = x->parent;
        while (x == y->right) {
            x = y;
            y = y->parent;
        }
        if (y == root)
            return nil;
        return y;
    }
}

void _rbtree_delete(rbtree* tree, rbnode* x) {
    rbnode* root = tree->root->left;
    rbnode* temp;

    while ((!x->red) && (root != x)) {
        if (x == x->parent->left) {
            temp = x->parent->right;
            if (temp->red) {
                temp->red = 0;
                x->parent->red = 1;
                left_rotate(tree, x->parent);
                temp = x->parent->right;
            }
            if ((!temp->right->red) && (!temp->left->red)) {
                temp->red = 1;
                x = x->parent;
            }
            else {
                if (!temp->right->red) {
                    temp->left->red = 0;
                    temp->red = 1;
                    right_rotate(tree, temp);
                    temp = x->parent->right;
                }
                temp->red = x->parent->red;
                x->parent->red = 0;
                temp->right->red = 0;
                left_rotate(tree, x->parent);
                x = root;
            }
        }
        else {
            temp = x->parent->left;
            if (temp->red) {
                temp->red = 0;
                x->parent->red = 1;
                right_rotate(tree, x->parent);
                temp = x->parent->left;
            }
            if ((!temp->right->red) && (!temp->left->red)) {
                temp->red = 1;
                x = x->parent;
            }
            else {
                if (!temp->left->red) {
                    temp->right->red = 0;
                    temp->red = 1;
                    left_rotate(tree, temp);
                    temp = x->parent->left;
                }
                temp->red = x->parent->red;
                x->parent->red = 0;
                temp->left->red = 0;
                right_rotate(tree, x->parent);
                x = root;
            }
        }
    }
    x->red = 0;
}

/// <summary>
/// 
/// </summary>
/// <param name="tree"></param>
/// <param name="z"></param>
void rbtree_delete(rbtree* tree, rbnode* z) {
    rbnode* y;
    rbnode* x;
    rbnode* nil = tree->nil;
    rbnode* root = tree->root;

    y = ((z->left == nil) || (z->right == nil)) ? z : rbtree_successor(tree, z);
    x = (y->left == nil) ? y->right : y->left;
    if (root ==
        (x->parent = y->parent)) {
        root->left = x;
    }
    else {
        if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }
    }
    if (y != z) {
        if (!(y->red))
            _rbtree_delete(tree, x);

        tree->destroydata(z->data);
        y->left = z->left;
        y->right = z->right;
        y->parent = z->parent;
        y->red = z->red;
        z->left->parent = z->right->parent = y;
        if (z == z->parent->left) {
            z->parent->left = y;
        }
        else {
            z->parent->right = y;
        }
        free(z);
    }
    else {
        tree->destroydata(y->data);
        if (!(y->red))
            _rbtree_delete(tree, x);
        free(y);
    }
}
