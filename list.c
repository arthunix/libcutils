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
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "common.h"


/* Builder Members: */

/// <summary>
/// Constructs a list container object and allocate a list size will store the head, 
/// tail pointers and size.
/// </summary>
/// <returns>A pointer to the created list</returns>
list* list_create(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
) {
    list* new_list = (list*)malloc_v(sizeof(list*));
    new_list->cmpfun = _cmpfun;
    new_list->destroydata = _destroydata;
    new_list->printdata = _printdata;
    new_list->pHead = NULL;
    new_list->pTail = NULL;
    new_list->size = 0;
    new_list->isItSorted = 1;
    return new_list;
}

/// <summary>
/// This destroys all container elements, and deallocates all the storage capacity 
/// allocated by the list container using its allocator.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
void list_destroy(list* list_input) {
    listnode* aux = list_input->pHead;

    if (list_input->size == 0) {
        return;
    }

    if (list_input->pHead == list_input->pTail) {
        free(aux);
    }
    else {
        listnode* aux = list_input->pHead;
        while (aux->pNext != NULL) {
            listnode* node_to_be_deleted = aux;
            aux = aux->pNext;
            list_input->destroydata(node_to_be_deleted);
        }
        free(aux);
    }
}

/// <summary>
/// Adds a new element at the end of the list container, after its current last element.
/// The content of val is copied(or moved) to the new element. This effectively increases 
/// the container size by one.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
/// <param name="new_value">: The data will be pushed into the list</param>
void list_push_back(list* list_input, void* new_value) {
    listnode* tmp_head = list_input->pHead;
    listnode* tmp_tail = list_input->pTail;
    if (list_input->size == 0) {
        listnode* new_node = (listnode*)malloc_v(sizeof(listnode));
        new_node->data = new_value;
        new_node->pPrev = NULL;
        new_node->pNext = NULL;
        list_input->pHead = new_node;
        list_input->pTail = new_node;
        list_input->size += 1;
        return;
    }
    listnode* new_node = (listnode*)malloc_v(sizeof(listnode));
    new_node->data = new_value;
    new_node->pPrev = tmp_tail;
    new_node->pNext = NULL;
    tmp_tail->pNext = new_node;
    list_input->pTail = new_node;
    list_input->size += 1;
    return;
}


/// <summary>
/// Removes the last element in the list container, effectively reducing its size by one.
/// This destroys the removed element.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
void list_pop_back(list* list_input) {
    //node* tmp_head = list_input->head;
    listnode* tmp_tail = list_input->pTail;
    if (list_input->size == 0) {
        return;
    }

    if (list_input->pHead == list_input->pTail) {
        free(tmp_tail);
        list_input->size -= 1;
        return;
    }

    list_input->pTail = list_input->pTail->pPrev;
    tmp_tail->pPrev->pNext = NULL;
    list_input->destroydata(tmp_tail->data);
    free(tmp_tail);
    list_input->size -= 1;
    return;
}

void list_print(
    const list* list_input,
    size_t p_start,
    size_t p_numOfElements
) {
    if ((p_numOfElements < p_start) || (p_start < 0) || (p_numOfElements <= 0))
        return;

    listnode* curr = list_input->pHead;

    fprintf(stdout, "< ");
    for (size_t i = p_start; i < p_numOfElements - 1; i++)
    {
        /* We cast our array to char, it's like a byte array and we work with
        bytes because it's easy, we catch a poiter to the beggining of the data,
        to catch the next element of array we go right the sizeof the data type*/
        (list_input->printdata)((void*)(curr->data));
        curr = curr->pNext;
        fprintf(stdout, ", ");
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
        _flushall();
#elif defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)
        fflush(NULL);
#endif
    }
    curr = list_input->pTail;
    (list_input->printdata)((void*)(curr->data));
    fprintf(stdout, " >");

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
    _flushall();
#elif defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)
    fflush(NULL);
#endif
}