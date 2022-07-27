#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>

static void* safe_malloc(size_t n, unsigned long line)
{
    void* ptr = malloc(n);
    if (!ptr) {
        fprintf(stderr, "At [%s:%ul] unable to allocate (%ul bytes) of memory\n",
            __FILE__, line, (unsigned long)n);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

#define malloc_v(n) safe_malloc(n, __LINE__)

#endif // !COMMON_H