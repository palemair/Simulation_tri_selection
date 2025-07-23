#include <stdio.h>
#include "../include/xalloc.h"

/* malloc custom to avoid error test */
void* xmalloc (size_t size)
{
    void* value = NULL;

    value = malloc (size);
    if (value == NULL)
    {
        perror ("Virtual memory exhausted");
        exit (EXIT_FAILURE);
    }

    return value;
}

/* calloc custom */
void* xcalloc (size_t elemcount, size_t elemsize)
{
    void* value = NULL;

    value = calloc (elemcount, elemsize);
    if (value == NULL)
    {
        perror ("Virtual memory exhausted");
        exit (EXIT_FAILURE);
    }

    return value;
}

/* realloc custom to avoid error test */
void* xreallocarray (void* ptr, size_t nmemb, size_t size)
{
    void* value = realloc (ptr, nmemb * size);

    if (value == 0)
    {
        perror ("Virtual memory exhausted");
        exit (EXIT_FAILURE);
    }
    return value;
}
