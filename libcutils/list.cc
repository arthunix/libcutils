#include "list.hh"
#include "common.hh"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// <summary>
/// Returns the number of elements in the list container.
/// </summary>
/// <param name="list_input">: A pointer to the list container will be mesured</param>
/// <returns>The size of the list</returns>
unsigned int list_size(const list* list_input) {
    return list_input->size;
}


/// <summary>
/// Returns whether the list container is empty (i.e. whether its size is 0).
/// </summary>
/// <param name="list_input">: A pointer to the list container will be mesured</param>
/// <returns>A boolean value that mean if the list is empity or not</returns>
unsigned int list_empty(const list* list_input) {
    if (list_size(list_input) == 0) {
        return 1;
    }
    return 0;
}


/* Builder Members: */

/// <summary>
/// Constructs a list container object and allocate a list size will store the head, 
/// tail pointers and size.
/// </summary>
/// <returns>A pointer to the created list</returns>
list* list_contructor(
    int (*_cmpfun)(const void*, const void*),
    void (*_destroydata)(void*),
    void (*_printdata)(const void*)
) {
    list* new_list = (list*)malloc_v(sizeof(list*));
    new_list->cmpfun = _cmpfun;
    new_list->destroydata = _destroydata;
    new_list->printdata = _printdata;
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;
    return new_list;
}


/// <summary>
/// This destroys all container elements, and deallocates all the storage capacity 
/// allocated by the list container using its allocator.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
void list_destructor(list* list_input){
    listnode* aux = list_input->head;
    if (list_empty(list_input)) {
        return;
    }

    if (list_input->head == list_input->tail) {
        free(aux);
    } else {
        listnode* aux = list_input->head;
        while (aux->next != NULL) {
            listnode* node_to_be_deleted = aux;
            aux = aux->next;
            list_input->destroydata(node_to_be_deleted);
        }
        free(aux);
    }
}


/* Modifiers Members: */

/// <summary>
/// Inserts a new element at the beginning of the list, right before its current first element. 
/// The content of val is copied(or moved) to the inserted element.
/// This effectively increases the container size by one.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
/// <param name="new_value">: The data will be pushed into the list</param>
void list_push_front(list* list_input, void* new_value) {
    listnode* tmp_head = list_input->head;
    listnode* tmp_tail = list_input->tail;

    if (list_empty(list_input)) {
        listnode* new_node = (listnode*)malloc_v(sizeof(listnode));
        new_node->data = new_value;
        new_node->prev = NULL;
        new_node->next = NULL;
        list_input->head = new_node;
        list_input->tail = new_node;
        list_input->size += 1;
        return;
    }
    listnode* new_node = (listnode*)malloc_v(sizeof(listnode));
    new_node->data = new_value;
    new_node->prev = NULL;
    new_node->next = tmp_head;
    tmp_head->prev = new_node;
    list_input->head = new_node;
    list_input->size += 1;
    return;
}


/// <summary>
/// Removes the first element in the list container, effectively reducing its size by one.
/// This destroys the removed element.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
void list_pop_front(list* list_input) {
    listnode* tmp_head = list_input->head;
    //node* tmp_tail = list_input->tail;
    if (list_empty(list_input)) {
        return;
    }

    if (list_input->head == list_input->tail) {
        free(tmp_head);
        list_input->size -= 1;
        return;
    }
    list_input->head = list_input->head->next;
    tmp_head->next->prev = NULL;
    list_input->destroydata(tmp_head->data);
    free(tmp_head);
    list_input->size -= 1;
    return;
}


/// <summary>
/// Adds a new element at the end of the list container, after its current last element.
/// The content of val is copied(or moved) to the new element. This effectively increases 
/// the container size by one.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
/// <param name="new_value">: The data will be pushed into the list</param>
void list_push_back(list* list_input, void* new_value) {
    listnode* tmp_head = list_input->head;
    listnode* tmp_tail = list_input->tail;
    if (list_empty(list_input)) {
        listnode* new_node = (listnode*)malloc_v(sizeof(listnode));
        new_node->data = new_value;
        new_node->prev = NULL;
        new_node->next = NULL;
        list_input->head = new_node;
        list_input->tail = new_node;
        list_input->size += 1;
        return;
    }
    listnode* new_node = (listnode*)malloc_v(sizeof(listnode));
    new_node->data = new_value;
    new_node->prev = tmp_tail;
    new_node->next = NULL;
    tmp_tail->next = new_node;
    list_input->tail = new_node;
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
    listnode* tmp_tail = list_input->tail;
    if (list_empty(list_input)) {
        return;
    }

    if (list_input->head == list_input->tail) {
        free(tmp_tail);
        list_input->size -= 1;
        return;
    }
    list_input->tail = list_input->tail->prev;
    tmp_tail->prev->next = NULL;
    list_input->destroydata(tmp_tail->data);
    free(tmp_tail);
    list_input->size -= 1;
    return;
}

/// <summary>
/// Removes from the list container either a single element. This effectively 
/// reduces the container size by the number of elements removed, which are destroyed.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
/// <param name="position">: the effective index position will be removed</param>
void list_erase(list* list_input, unsigned int position) {
    if (list_input->size - 1 < position) {
        fprintf(stderr, "Out of range, cannot delete a note at that position");
        return;
    } else {
        //node* aux = list_input->head;
        if (position == 0) {
            list_pop_front(list_input);
        } else if (position == list_input->size - 1) {
            list_pop_back(list_input);
        } else {
            listnode* to_remove = list_input->head;
            for (unsigned int i = 1; i <= position; i++) {
                to_remove = to_remove->next;
            }
            //node* to_remove_next = to_remove->next;
            //node* to_remove_prev = to_remove->prev;
            to_remove->prev->next = to_remove->next;
            to_remove->next->prev = to_remove->prev;
            list_input->size -= 1;
            list_input->destroydata(to_remove->data);
            free(to_remove);
        }
    }
}


/// <summary>
/// Resizes the container so that it contains n elements. If n is smaller than the current 
/// container size, the content is reduced to its first n elements, removing those beyond 
/// (and destroying them).If n is greater than the current container size, thecontent is 
/// expanded by inserting at the end as many elements as needed to reach a size of n.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
/// <param name="sz">the new size of the resized container</param>
/// <param name="value">value of the new initalized data (you can pass a void Data)</param>
void list_resize(list* list_input, unsigned int sz, void* value) {
    //unsigned int sz_temp = size(list_input);
    if (sz < list_input->size) {
        while (list_input->size != sz) {
            list_pop_back(list_input);
        }
    } else {
        while (list_input->size != sz) {
            list_push_back(list_input, value);
        }
    }
}


/// <summary>
/// Removes all elements from the list container (which are destroyed), 
/// and leaving the container with a size of 0.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be modified</param>
void list_clear(list* list_input) {
    while (list_input->size != 0) {
        list_pop_back(list_input);
    }
}


/* Element Access Members: */

/// <summary>
/// Returns a reference to the first element in the list container.
/// Calling this function on an empty container causes undefined behavior.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be analysed</param>
/// <returns>A reference to the first element in the list container</returns>
listnode* list_front(const list* list_input) {
    if (!list_empty(list_input)) {
        return list_input->head;
    }
    fprintf(stderr, "Calling this function on an empty container causes undefined behavior");
    return NULL;
}


/// <summary>
/// Returns a reference to the last element in the list container.
/// Calling this function on an empty container causes undefined behavior.
/// </summary>
/// <param name="list_input">: A pointer to the list container to be analysed</param>
/// <returns> A reference to the last element in the list container</returns>
listnode* list_back(const list* list_input) {
    if (!list_empty(list_input)) {
        return list_input->tail;
    }
    fprintf(stderr, "Calling this function on an empty container causes undefined behavior");
    return NULL;
}


/// <summary>
/// This is the generic list printing function... just call the user defined ListData print
/// function and print element by element
/// </summary>
/// <param name="list_input">: A pointer to the list container to be printed</param>
/// <param name="printfunction">: A pointer to a print function</param>
void list_print(
    const list* list_input,
    size_t p_start,
    size_t p_numOfElements
) {
    if ((p_numOfElements < p_start) || (p_start < 0) || (p_numOfElements <= 0))
        return;

    listnode* curr = list_input->head;

    fprintf(stdout, "< ");
    for (size_t i = p_start; i < p_numOfElements - 1; i++)
    {
        /* We cast our array to char, it's like a byte array and we work with
        bytes because it's easy, we catch a poiter to the beggining of the data,
        to catch the next element of array we go right the sizeof the data type*/
        (list_input->printdata)(curr->data);
        curr = curr->next;
        fprintf(stdout, ", ");
    }
    curr = list_input->tail;
    (list_input->printdata)(curr->data);
    fprintf(stdout, ">");
    _flushall();
}