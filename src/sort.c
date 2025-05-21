#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/sort.h"

void shuffle_fy (void* tb, size_t sizetb, size_t size)
{
    srand (time (NULL));
    unsigned char* ptr = tb;
    unsigned char temp[size];
    unsigned int j = 0;

    for (size_t i = sizetb - 1; i > 0; i--)
    {
        j = rand() % i;
        memcpy(temp,(ptr + (size * i)),size);
        memcpy((ptr + (size * i)),(ptr + (size * j)),size);
        memcpy((ptr + (size * j)),temp,size);
    }
}

void print_array (const int* ptr, size_t nbelem)
{
    for (size_t u = 0; u < nbelem; u++)
    {
        printf ("%4c | ", *ptr++);
    }
    printf ("\n");
}

int selectsort (int* tab, size_t nbelem)
{
    int tmp;
    size_t j, indexmin;

    for (size_t i = 0; i < nbelem - 1; i++)
    {
        indexmin = i;
        for (j = i + 1; j < nbelem; j++)
        {
            if (tab[j] < tab[indexmin]) indexmin = j;
        }

        tmp = tab[i];
        tab[i] = tab[indexmin];
        tab[indexmin] = tmp;
    }
    return EXIT_SUCCESS;
}
