/* sort.c */
#ifndef _COLORS
#define _COLORS

#include<stdlib.h>
#include <SDL2/SDL.h>

struct Graph {
    unsigned short w;
    unsigned short h;
    unsigned char nb;
    unsigned char dw;
    unsigned char marge;
    unsigned char padding;
};
    
extern   SDL_Color White;
extern   SDL_Color Silver; 
extern   SDL_Color Gray ;
extern   SDL_Color Black ;
extern   SDL_Color Red ;
extern   SDL_Color Maroon ;
extern   SDL_Color Yellow ;
extern   SDL_Color Olive ;
extern   SDL_Color Lime ;
extern   SDL_Color Green ;
extern   SDL_Color Aqua ;
extern   SDL_Color Teal ;
extern   SDL_Color Blue ;
extern   SDL_Color Navy ;
extern   SDL_Color Fuchsia ;
extern   SDL_Color Purple ;
/* prototypes */
void init_graph(struct Graph *gr);
int chg_color(SDL_Renderer *rend, const SDL_Color *col);
int clear_renderer(SDL_Renderer *rend, const SDL_Color *col);
void Draw (SDL_Rect* t, int* tbint, size_t step,
           SDL_Renderer* rend,
           const SDL_Color* col1,
           const SDL_Color* col2,
           struct Graph *pGr);

#endif
