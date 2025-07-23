/* some common functions */ 

#ifndef _ALLOC
#define _ALLOC

#include <stdlib.h>

/* malloc custom to avoid error test */
void* xmalloc (size_t size);
/* calloc custom to avoid error test */
void* xcalloc (size_t elemcount, size_t elemsize);
/* reallocarray custom to avoid error test */
void* xreallocarray (void* ptr, size_t nmemb, size_t size);
/* delete left and right space char + double quotes in a field */
#endif
