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
