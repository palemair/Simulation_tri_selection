/* sort.c */
#ifndef _DRAWING
#define _DRAWING

#include <SDL2/SDL.h>

struct Graph {
    unsigned short w;
    unsigned short h;
    unsigned char nb;
    unsigned char dw;
    unsigned char marge;
    unsigned char padding;
};
    
/* prototypes */
struct Graph* init_graph(struct Graph *gr, int, int,int);
void destroy_graph(void);

void Draw(SDL_Rect *t, int *tbint, size_t step, SDL_Renderer *rend, const SDL_Color *col1, const SDL_Color *col2, struct Graph *pGr);

void DrawRoundedRect(SDL_Renderer *rend, int x, int y, int r, int w, int h);

#endif
