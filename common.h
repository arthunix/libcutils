#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
    #if defined(LIBCUTILS_EXPORTS)
        #define LIBCUTILS_API __declspec(dllexport)
    #else
        #define LIBCUTILS_API __declspec(dllimport)
    #endif
#elif defined(__linux__) || defined(UNIX) || defined(__unix__) || defined(LINUX)
    #if defined(LIBCUTILS_EXPORTS)
        #define LIBCUTILS_API __attribute__((visibility("default")))
    #else
        #define LIBCUTILS_API
    #endif
#else
    #define LIBCUTILS_API
    #pragma WARNING: Unknown dynamic link import/export semantics.
#endif


#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// 
/// </summary>
/// <param name="n"></param>
/// <param name="line"></param>
/// <returns></returns>
LIBCUTILS_API void* safe_malloc(size_t n, unsigned long line);

#define malloc_v(n) safe_malloc(n, __LINE__)

/// <summary>
/// This is a generic array printing function, we can just pass the function for
/// printing any data type you want.
/// </summary>
/// <param name="data">: A pointer to the beggining of the array of Any Data Type</param>
/// <param name="sizeOfTheType">: just pass as argument the function sizeof(dataTypeOfPassedArray)</param>
/// <param name="p_start">: The index of the element you want to start printing</param>
/// <param name="p_numOfElements">: The Size of The Array, the number of elements to print</param>
/// <param name="printFunction">: The function will be used to print a singe data type element</param>
LIBCUTILS_API void print_array(
    void* data,
    size_t sizeOfTheType,
    size_t p_start,
    size_t p_numOfElements,
    void (*printfun)(const void*));

#ifdef __cplusplus
}
#endif

#endif // !COMMON_H
