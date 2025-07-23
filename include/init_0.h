/* sort.c */
#ifndef _INITIALIZE
#define _INITIALIZE
#include <SDL2/SDL.h>
/* prototypes */
int init_0(SDL_Window **pwin, SDL_Renderer **prend, int W, int H, const char *titre);
void destroy_0(SDL_Window **pwin, SDL_Renderer **prend);
int init_texture(SDL_Texture **ptext, SDL_Renderer *prend, int x, int y);
void shuffle_fy (void* tb, size_t sizetb, size_t size);

#endif
