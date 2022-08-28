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

#include "stack.h"
#include "common.h"

/* Capacity Members: */

/// <summary>
/// Measure the size the number of elements in the stack container.
/// </summary>
/// <param name="stack_input"> A pointer to the Stack container</param>
/// <returns>the number of elements in the stack container</returns>
unsigned int stack_size(const stack* stack_input)
{
    return stack_input->size;
}

/// <summary>
/// Measure whether the stack container is empty (i.e. whether its size is 0).
/// </summary>
/// <param name="stack_input">: A pointer to the Stack container</param>
/// <returns>A boolean-like value tell us if the Stack Container is void</returns>
int stack_empty(const stack* stack_input)
{
    if (stack_size(stack_input) == 0)
    {
        return 1;
    }
    return 0;
}

/* Builder Members: */

/// <summary>
/// Constructs a list container object and allocate a list size will store the head,
/// tail pointiersand size.
/// </summary>
/// <returns>A pointer to the new allocated Stack</returns>
stack* stack_contructor(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
) {
    stack* new_stack = (stack*)malloc_v(sizeof(stack*));

    new_stack->cmpfun = _cmpfun;
    new_stack->destroydata = _destroydata;
    new_stack->printdata = _printdata;

    new_stack->top = NULL;
    new_stack->size = 0;
    return new_stack;
}


/// <summary>
/// This destroys all container elements, and deallocates all the storage capacity
/// allocated by the stack container using its allocator.
/// </summary>
/// <param name="stack_input">: A pointer to the Stack container</param>
void stack_destructor(stack* stack_input) {
    stacknode* aux = stack_input->top;
    if (stack_empty(stack_input))
        return;

    if (stack_size(stack_input) == 1)
    {
        free(aux);
    }
    else
    {
        stacknode* aux = stack_input->top;
        while (aux->down != NULL)
        {
            stacknode* node_to_be_deleted = aux;
            stack_input->destroydata(node_to_be_deleted->data);
            aux = aux->down;
            free(node_to_be_deleted);
        }
        free(aux);
    }
}


/// <summary>
/// Returns a reference to the top element in the stack.
/// </summary>
/// <param name="stack_input">: A pointer to the Stack container</param>
/// <returns>A pointer to the top element of the list</returns>
stacknode* stack_top(stack* stack_input) {
    return stack_input->top;
}


/// <summary>
/// Inserts a new element at the top of the stack, above its current top element. 
/// The content of this new element is initialized to a copy of new_inserted_data.
/// </summary>
/// <param name="stack_input">A pointer to the stack container</param>
/// <param name="new_value">: The data will be pushed into the stack</param>
void stack_push(stack* stack_input, void* new_inserted_data) {
    if (stack_empty(stack_input)) {
        stacknode* new_node = (stacknode*)malloc_v(sizeof(stacknode));
        new_node->data = new_inserted_data;
        new_node->down = NULL;
        new_node->up = NULL;
        stack_input->top = new_node;
        stack_input->size += 1;
        return;
    }
    stacknode* new_node = (stacknode*)malloc_v(sizeof(stacknode));
    stack_input->top->up = new_node;
    new_node->data = new_inserted_data;
    new_node->down = stack_input->top;
    new_node->up = NULL;
    stack_input->top = new_node;
    stack_input->size += 1;
}


/// <summary>
/// Removes the element on top of the stack, effectively reducing its size by one.
/// </summary>
/// <param name="stack_input">A pointer to the stack container</param>
void stack_pop(stack* stack_input) {
    stacknode* tmp_top = stack_input->top;
    if (stack_empty(stack_input)) {
        return;
    }

    if (tmp_top->down == NULL) {
        stack_input->destroydata(tmp_top->data);
        free(tmp_top);
        stack_input->size -= 1;
        return;
    }

    stack_input->top = stack_input->top->down;
    tmp_top->down->up = NULL;
    stack_input->destroydata(tmp_top->data);
    free(tmp_top);
    stack_input->size -= 1;
    return;
}


/// <summary>
/// This is the generic stack printing function... just call the user defined StackData print
/// function and print element by element
/// </summary>
/// <param name="list_input">: A pointer to the stack container to be printed</param>
/// <param name="printfunction">: A pointer to a print function</param>
void stack_print(const stack* list_input) {
    stacknode* curr = list_input->top;
    fprintf(stdout, "< ");
    fprintf(stdout, "(TOP->)");
    for (unsigned int i = 0; i < (list_input->size - 1); i++) {
        (list_input->printdata)(curr->data);
        curr = curr->down;
        fprintf(stdout, ", ");
    }
    (list_input->printdata)(curr->data);
    fprintf(stdout, ">\n");
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
    _flushall();
#elif defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)
    fflush(NULL);
#endif
}