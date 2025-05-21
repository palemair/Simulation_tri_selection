/* sort.c */
#ifndef _SORT
#define _SORT

#include<stdlib.h>
#include<time.h>
/* prototypes */
/* Mélange un tableau tb de int de n éléments selon algo fisher_yates */
void shuffle_fy(void* tb,size_t n,size_t size);

/* tri selection sur array de int de nbelem éléments */
int selectsort(int *array, size_t nbelem);

/* affiche tableau */
void print_array(const int *ptr, size_t nbelem);

#endif
