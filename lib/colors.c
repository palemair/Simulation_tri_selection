#include <SDL2/SDL.h>
#include "../include/colors.h"
#include "../include/tpile.h"

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

int init_graph (SDL_Window **pwin, SDL_Renderer **prend,struct Graph *gr,const char *titre)
{
    gr->dw = (10 * gr->w) / ((11 * gr->nb) + 1);
    gr->marge = gr->dw / 10;
    gr->padding = ((gr->w) - ((gr->marge * (gr->nb - 1)) + (gr->dw * gr->nb))) / 2;

    if (0 != SDL_Init (SDL_INIT_VIDEO))
    {
        fprintf (stderr, "Erreur SDL_Init : %s", SDL_GetError ());
        SDL_Quit ();
        exit(EXIT_FAILURE);
    }

    *pwin = SDL_CreateWindow(titre,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,gr->w, gr->h, 0);
    if (*pwin == NULL)
    {
        fprintf (stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError ());
        SDL_Quit ();
        exit(EXIT_FAILURE);
    }

    *prend = SDL_CreateRenderer(*pwin,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*prend == NULL)
    {
        fprintf (stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError ());
        SDL_DestroyWindow (*pwin);
        SDL_Quit ();
        exit(EXIT_FAILURE);
    }
    return(EXIT_SUCCESS);
}

void destroy_graph(SDL_Window **pwin, SDL_Renderer **prend)
{
    if (NULL != *prend)
        SDL_DestroyRenderer (*prend);
    if (NULL != *pwin)
        SDL_DestroyWindow (*pwin);
    SDL_Quit ();
}

int init_texture(SDL_Texture **ptext,SDL_Renderer *prend,unsigned int x,unsigned int y)
{
    *ptext = SDL_CreateTexture (prend, 
                               SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_TARGET,
                               x,
                               y);
    if (NULL == *ptext)
    {
        fprintf (stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError ());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void destroy_texture(SDL_Texture *ptext)
{
    if (NULL != ptext)
    {
        free(ptext);
    }
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
