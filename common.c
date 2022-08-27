#include "common.h"

void* safe_malloc(size_t n, unsigned long line)
{
    void* ptr = malloc(n);
    if (!ptr) {
        fprintf(stderr, "At [%s:%lu] unable to allocate (%lu bytes) of memory\n",
            __FILE__, line, (unsigned long)n);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void print_array(
    void* data,
    size_t sizeOfTheType,
    size_t p_start,
    size_t p_numOfElements,
    void (*printfun)(const void*))
{
    if ((p_numOfElements < p_start) || (p_start < 0) || (p_numOfElements <= 0))
        return;

    fprintf(stdout, "< ");
    for (size_t i = p_start; i < p_numOfElements - 1; i++)
    {
        /* We cast our array to char, it's like a byte array and we work with
        bytes because it's easy, we catch a poiter to the beggining of the data,
        to catch the next element of array we go right the sizeof the data type*/
        void* curr_ptr = ((char*)data + (i * sizeOfTheType));
        (printfun)(curr_ptr);
        fprintf(stdout, ", ");
    }
    void* curr_ptr = ((char*)data + ((p_numOfElements - 1) * sizeOfTheType));
    (printfun)(curr_ptr);
    fprintf(stdout, ">");
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
    _flushall();
#elif defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)
    fflush(NULL);
#endif
}
