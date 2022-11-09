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

#include "cutils.h"

doublelinkedlist* double_linked_list_create(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
) {
    doublelinkedlist* new_list = (doublelinkedlist*)malloc_v(sizeof(doublelinkedlist*));

    new_list->protofun.cmpfun = _cmpfun;
    new_list->protofun.destroydata = _destroydata;
    new_list->protofun.printdata = _printdata;

    new_list->pHead = NULL;
    new_list->pTail = NULL;
    new_list->size = 0;

    return new_list;
}

void double_linked_list_destroy(doublelinkedlist* double_linked_list) {
    while (double_linked_list->size > 0) {
        double_linked_list_pop_back(double_linked_list);
    }
}

circularlist* circular_linked_list_create(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
) {
    circularlist* new_list = (circularlist*)malloc_v(sizeof(circularlist*));

    new_list->protofun.cmpfun = _cmpfun;
    new_list->protofun.destroydata = _destroydata;
    new_list->protofun.printdata = _printdata;

    new_list->pHead = NULL;
    new_list->pTail = NULL;
    new_list->size = 0;

    return new_list;
}

queue* queue_create(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
) {
    queue* new_queue = (queue*)malloc_v(sizeof(queue*));

    new_queue->protofun.cmpfun = _cmpfun;
    new_queue->protofun.destroydata = _destroydata;
    new_queue->protofun.printdata = _printdata;

    new_queue->pHead = NULL;
    new_queue->pTail = NULL;
    new_queue->size = 0;

    return new_queue;
}

listnode* double_linked_list_insert_back(doublelinkedlist* double_linked_list, const void* value) {
    listnode* tmp_tail = double_linked_list->pTail;
    listnode* new_node = (listnode*)malloc_v(sizeof(listnode));

    if (double_linked_list->size < 0) {
        fprintf(stderr, "Error at %s at line %lu list size is invalid\n", __FILE__, __LINE__);
        return;
    }

    if (double_linked_list->size == 0) {
        new_node->data = value;
        new_node->pNext = NULL;
        new_node->pPrev = NULL;
        double_linked_list->pHead = new_node;
        double_linked_list->pTail = new_node;
        double_linked_list->isItSorted = 1;
        double_linked_list->size += 1;
    }
    else {
        new_node->data = value;
        new_node->pNext = NULL;
        new_node->pPrev = tmp_tail;
        tmp_tail->pNext = new_node;
        double_linked_list->pTail = new_node;
        double_linked_list->size += 1;
    }

    return new_node;
}

listnode* double_linked_list_insert_front(doublelinkedlist* double_linked_list, const void* value) {
    listnode* tmp_head = double_linked_list->pHead;
    listnode* new_node = (listnode*)malloc_v(sizeof(listnode));

    if (double_linked_list->size < 0) {
        fprintf(stderr, "Error at %s at line %lu list size is invalid\n", __FILE__, __LINE__);
        return;
    }

    if (double_linked_list->size == 0) {
        new_node->data = value;
        new_node->pNext = NULL;
        new_node->pPrev = NULL;
        double_linked_list->pHead = new_node;
        double_linked_list->pTail = new_node;
        double_linked_list->isItSorted = 1;
        double_linked_list->size += 1;
    }
    else {
        new_node->data = value;
        new_node->pPrev = NULL;
        new_node->pNext = tmp_head;
        tmp_head->pPrev = new_node;
        double_linked_list->pHead = new_node;
        double_linked_list->size += 1;
    }

    return new_node;
}

listnode* double_linked_list_insert_at_index(doublelinkedlist* double_linked_list, const void* value, unsigned int position) {

    if (double_linked_list->size < 0) {
        fprintf(stderr, "Error at %s at line %lu list size is invalid\n", __FILE__, __LINE__);
        return;
    }

    if (position > (double_linked_list->size + 1)) {
        fprintf(stderr, "Error at %s at line %lu list size is invalid : it is not possible to retrieve at this position\n", __FILE__, __LINE__);
        return;
    }
    else {
        if (position == 0) {
            return double_linked_list_insert_front(double_linked_list, value);
        }
        else if (position == double_linked_list->size) {
            return double_linked_list_insert_back(double_linked_list, value);
        }
    }

    listnode* it = double_linked_list->pHead;

    for (int i; i < position; i++) {
        it = it->pNext;
    }

    listnode* tmp_prev = it;
    listnode* tmp_next = it->pNext;

    listnode* new_node = (listnode*)malloc_v(sizeof(listnode));
    new_node->data = value;
    new_node->pNext = tmp_next;
    new_node->pPrev = tmp_prev;
    tmp_prev->pNext = new_node;
    tmp_next->pPrev = new_node;
    double_linked_list->size += 1;

    return new_node;
}

listnode* double_linked_list_search(doublelinkedlist* double_linked_list, const void* value) {
    listnode* it = double_linked_list->pHead;

    for (int i; i < double_linked_list->size; i++) {
        if (double_linked_list->protofun.cmpfun(value, it->data)) {
            return it;
        }
        it = it->pNext;
    }

    return NULL;
}

void double_linked_list_pop_back(doublelinkedlist* double_linked_list) {
    listnode* tmp_tail = double_linked_list->pTail;

    if (double_linked_list->size == 0) {
        return;
    }

    if (double_linked_list->size == 1) {
        tmp_tail->pNext == NULL;
        tmp_tail->pPrev == NULL;
        double_linked_list->protofun.destroydata(tmp_tail->data);
        free(tmp_tail);
    }

    listnode* tmp_prev = tmp_tail->pPrev;
    tmp_tail->pPrev = NULL;
    tmp_prev->pNext = NULL;
    double_linked_list->protofun.destroydata(tmp_tail->data);
    free(tmp_tail);
    double_linked_list->size -= 1;
}

void double_linked_list_pop_front(doublelinkedlist* double_linked_list) {
    listnode* tmp_head = double_linked_list->pHead;

    if (double_linked_list->size == 0) {
        return;
    }

    if (double_linked_list->size == 1) {
        tmp_head->pNext == NULL;
        tmp_head->pPrev == NULL;
        double_linked_list->protofun.destroydata(tmp_head->data);
        free(tmp_head);
    }

    listnode* tmp_next = tmp_head->pNext;
    tmp_head->pNext = NULL;
    tmp_next->pPrev = NULL;
    double_linked_list->protofun.destroydata(tmp_head->data);
    free(tmp_head);
    double_linked_list->size -= 1;
}

listnode double_linked_list_front(doublelinkedlist* double_linked_list) {
    return *(double_linked_list->pHead);
}

listnode double_linked_list_back(doublelinkedlist* double_linked_list) {
    return *(double_linked_list->pTail);
}

listnode double_linked_list_retrieve(doublelinkedlist* double_linked_list, unsigned int position) {
    listnode* it = double_linked_list->pHead;

    if (double_linked_list->size < 0) {
        fprintf(stderr, "Error at %s at line %lu list size is invalid\n", __FILE__, __LINE__);
        return;
    }

    if (position < (double_linked_list->size - 1)) {
        fprintf(stderr, "Error at %s at line %lu list size is invalid : it is not possible to retrieve at this position\n", __FILE__, __LINE__);
        return;
    }

    for (int i; i < position; i++) {
        it = it->pNext;
    }

    return *(it);
}

void double_linked_list_for_each(doublelinkedlist* double_linked_list, void (*operation)(listnode a)) {
    listnode* it = double_linked_list->pHead;

    for (int i; i < double_linked_list->size; i++) {
        operation(*it);
        it = it->pNext;
    }
}