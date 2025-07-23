#ifndef T_STACK
#define T_STACK

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

void init_stack(void);
bool stack_empty(void);
bool stack_push(SDL_Texture *v);
SDL_Texture *stack_pop(void);
int clear_stack(void);

#endif
