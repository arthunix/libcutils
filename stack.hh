#pragma once
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
this is the element of data inside the stack, you can use any Data Structure
here... You just need to to pass the entire element for the function insert.
In my first idea I through I need to pass a function pointer for constructing
the element: just a idiot idea, just pass it or create a function for it
*/
typedef struct StackElement {
    int Data;
}StackData, STACKData, STACKDATA, stackdata;

/*
This is the basic element node of the stack, we just have here the Data Element
a pointer to the down and to the up element
*/
typedef struct NodeS
{
    StackData data;
    struct NodeS* up;
    struct NodeS* down;
}nodes, NodeS, NODES, * NodeSPtr, * nodesptr, * NODESPTR;

/*
This is the basic element stack container, we just have here the size of the list
container and pointer to the top
*/
typedef struct Stack
{
    NodeS* top;
    unsigned int size;
}stack, Stack, STACK;

/*
This is the way you can define a function for printing the element in list container
on the way you want, just you just receive a parameter of the ListData and print as
you want like the exemple above:

void print(StackData dataOfTheNode){
    fprintf(stdout, "%i ", dataOfTheNode.Data);
}

void print(StackData dataOfTheNode){
    fprintf(stdout, "%i\n", dataOfTheNode.YearsOld);
    fprintf(stdout, "%s\n", dataOfTheNode.Email);
    fprintf(stdout, "%s\n", dataOfTheNode.firstName);
    fprintf(stdout, "%s\n", dataOfTheNode.lastName);
}
*/
typedef void (_StackPrintFunction)(const StackData);

/* Capacity Members: */

/// <summary>
/// Measure the size the number of elements in the stack container.
/// </summary>
/// <param name="stack_input"> A pointer to the Stack container</param>
/// <returns>the number of elements in the stack container</returns>
static inline unsigned int stack_size(const stack* stack_input)
{
    return stack_input->size;
}

/// <summary>
/// Measure whether the stack container is empty (i.e. whether its size is 0).
/// </summary>
/// <param name="stack_input">: A pointer to the Stack container</param>
/// <returns>A boolean-like value tell us if the Stack Container is void</returns>
static inline int stack_empty(const stack* stack_input)
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
static inline stack* stack_contructor() {
    stack* new_stack = (stack*)malloc(sizeof(stack*));
    if (new_stack == NULL) {
        fprintf(stderr, "memory fault, unable to allocate sizeof %llu at stack_contructor()", sizeof(stack));
        return NULL;
    }
    new_stack->top = NULL;
    new_stack->size = 0;
    return new_stack;
}


/// <summary>
/// This destroys all container elements, and deallocates all the storage capacity
/// allocated by the stack container using its allocator.
/// </summary>
/// <param name="stack_input">: A pointer to the Stack container</param>
static inline void stack_destructor(stack* stack_input) {
    nodes* aux = stack_input->top;
    if (stack_empty(stack_input))
        return;

    if (stack_size(stack_input) == 1)
    {
        free(aux);
    }
    else
    {
        nodes* aux = stack_input->top;
        while (aux->down != NULL)
        {
            nodes* node_to_be_deleted = aux;
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
static inline NodeS* stack_top(stack* stack_input) {
    return stack_input->top;
}


/// <summary>
/// Inserts a new element at the top of the stack, above its current top element. 
/// The content of this new element is initialized to a copy of new_inserted_data.
/// </summary>
/// <param name="stack_input">A pointer to the stack container</param>
/// <param name="new_value">: The data will be pushed into the stack</param>
static inline void stack_push(stack* stack_input, StackData new_inserted_data) {
    if (stack_empty(stack_input)) {
        nodes* new_node = (nodes*)malloc(sizeof(nodes));
        if (new_node == NULL) {
            fprintf(stderr, "memory fault, unable to allocate sizeof %llu at stack_push()", sizeof(nodes));
            return;
        }
        new_node->data = new_inserted_data;
        new_node->down = NULL;
        new_node->up = NULL;
        stack_input->top = new_node;
        stack_input->size += 1;
        return;
    }
    nodes* new_node = (nodes*)malloc(sizeof(nodes));
    if (new_node == NULL) {
        fprintf(stderr, "memory fault, unable to allocate sizeof %llu at stack_push()", sizeof(nodes));
        return;
    }
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
static inline void stack_pop(stack* stack_input) {
    nodes* tmp_top = stack_input->top;
    if (stack_empty(stack_input)) {
        return;
    }

    if (tmp_top->down == NULL) {
        free(tmp_top);
        stack_input->size -= 1;
        return;
    }
    stack_input->top = stack_input->top->down;
    tmp_top->down->up = NULL;
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
static inline void stack_print(const stack* list_input, _StackPrintFunction printfunction) {
    nodes* curr = list_input->top;
    fprintf(stdout, "< ");
    fprintf(stdout, "(TOP->)");
    for (unsigned int i = 0; i < list_input->size; i++) {
        (printfunction)(curr->data);
        curr = curr->down;
    }
    fprintf(stdout, ">\n");
    _flushall();
}

#endif // !STACK_H
