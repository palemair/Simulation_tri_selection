#include <SDL2/SDL.h>
#include "../include/colors.h"
#include "../include/drawing.h"

struct Graph * init_graph (struct Graph *gr, int W, int H, int N)
{
    gr->w = W;
    gr->h = H;
    gr->nb = N;
    gr->dw = (10 * gr->w) / ((11 * gr->nb) + 1);
    gr->marge = gr->dw / 10;
    gr->padding = ((gr->w) - ((gr->marge * (gr->nb - 1)) + (gr->dw * gr->nb))) / 2;

    return(gr);
}

void destroy_graph(void)
{
    return;
}

void Draw (SDL_Rect* t,
           int* tbint,
           size_t step,
           SDL_Renderer* rend,
           const SDL_Color* col1,
           const SDL_Color* col2,
           struct Graph* pGr){

    size_t L = pGr->nb;

    for (size_t i = 0; i < L; i++)
    {
        t[i].x = pGr->padding + pGr->marge * (i) + (pGr->dw * i);
        t[i].y = (pGr->h - (10 * tbint[i]))- 5* pGr->padding ;
        t[i].w = pGr->dw;
        t[i].h = (10 * tbint[i]);
    }
    active_color (rend, col1, 100);
    for (size_t s = 0; s <step; s++) SDL_RenderFillRect (rend, &t[s]);

    active_color (rend, col2, 100);
    for (size_t u = step ; u < L; u++) SDL_RenderFillRect (rend, &t[u]);
}

void DrawRoundedRect (SDL_Renderer* rend, int x, int y, int r, int w, int h)
{
    SDL_RenderDrawLine(rend,x,y-r,x,y-h);
    SDL_RenderDrawLine(rend,x+r,y-h-r,x+w-r,y-h-r);
}
