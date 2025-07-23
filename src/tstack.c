#include <stdbool.h>
#include "../include/tstack.h"

#define LEN 25

static SDL_Texture *ptext[LEN];
static int sp;
static int _MAX = LEN - 1;

void init_stack(void)
{
    sp = -1;
}

bool stack_empty(void)
{
    return sp == -1;
}

bool stack_push(SDL_Texture *t)
{
    if (sp < _MAX) 
    {
        ptext[++sp] = t;
        return true;
    }
    else 
    {
        fprintf(stderr,"%s\n","stack pleine !!");
        return false;
    }
}

SDL_Texture *stack_pop(void)
{
    if(!stack_empty())
    {
        return ptext[sp--];
    }
    else 
    {
        fprintf(stderr,"%s\n","stack vide !!");
        return NULL;
    }
}

int clear_stack(void)
{
   SDL_Texture * p = NULL;
   while(!stack_empty())
   {
       p = stack_pop();
       SDL_DestroyTexture(p);
   }
   return 0;
}
