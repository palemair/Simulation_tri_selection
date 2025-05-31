#include <SDL2/SDL.h>
#include "colors.h"

SDL_Color White = { 255, 255, 255, 255 };
SDL_Color Silver = { 192, 192, 192, 255 };
SDL_Color Gray = { 128, 128, 128, 255 };
SDL_Color Black = { 0, 0, 0, 255 };
SDL_Color Red = { 255, 0, 0, 255 };
SDL_Color Maroon = { 128, 0, 0, 255 };
SDL_Color Yellow = { 255, 255, 0, 255 };
SDL_Color Olive = { 128, 128, 0, 255 };
SDL_Color Lime = { 0, 255, 0, 255 };
SDL_Color Green = { 0, 128, 0, 255 };
SDL_Color Aqua = { 0, 255, 255, 255 };
SDL_Color Teal = { 0, 128, 128, 255 };
SDL_Color Blue = { 0, 0, 255, 255 };
SDL_Color Navy = { 0, 0, 128, 255 };
SDL_Color Fuchsia = { 255, 0, 255, 255 };
SDL_Color Purple = { 128, 0, 128, 255 };

void init_graph (struct Graph* gr)
{
    gr->dw = (10 * gr->w) / ((11 * gr->nb) + 1);
    gr->marge = gr->dw / 10;
    gr->padding = ((gr->w) - ((gr->marge * (gr->nb - 1)) + (gr->dw * gr->nb))) / 2;
}

int chg_color (SDL_Renderer* rend, const SDL_Color* col)
{
    if (0 < SDL_SetRenderDrawColor (rend, col->r, col->g, col->b, col->a))
        fprintf (stderr, "Erreur SDL : %s", SDL_GetError ());
    return 0;
}

int clear_renderer (SDL_Renderer* rend, const SDL_Color* col)
{
    if (0 < SDL_SetRenderDrawColor (rend, col->r, col->g, col->b, col->a))
        fprintf (stderr, "Erreur SDL : %s", SDL_GetError ());
    SDL_RenderClear (rend);
    return 0;
}

void Draw (SDL_Rect* t, int* tbint, size_t step,
           SDL_Renderer* rend, const SDL_Color* col1, const SDL_Color* col2, struct Graph* pGr)
{
    size_t L = pGr->nb;

    for (size_t i = 0; i < L; i++)
    {
        t[i].x = pGr->padding + pGr->marge * (i) + (pGr->dw * i);
        t[i].y = (pGr->h - (10 * tbint[i])) / 2;
        t[i].w = pGr->dw;
        t[i].h = (10 * tbint[i]);
    }
    chg_color (rend, col2);

    for (size_t s = 0; s <= step; s++) SDL_RenderFillRect (rend, &t[s]);

    chg_color (rend, col1);

    for (size_t u = step + 1; u < L; u++) SDL_RenderFillRect (rend, &t[u]);
}
