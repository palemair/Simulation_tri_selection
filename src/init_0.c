#include <SDL2/SDL.h>
#include <time.h>
#include <string.h>
#include "../include/init_0.h"
#include "../include/tstack.h"
#include "../include/colors.h"

int init_0 (SDL_Window **pwin, SDL_Renderer **prend,int W, int H,const char *titre)
{
    if (0 != SDL_Init (SDL_INIT_VIDEO))
    {
        fprintf (stderr, "Erreur SDL_Init : %s", SDL_GetError ());
        SDL_Quit ();
        exit(EXIT_FAILURE);
    }

    *pwin = SDL_CreateWindow(titre,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,W, H, 0);
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
    init_stack();
    init_color_html();

    return(EXIT_SUCCESS);
}

void destroy_0(SDL_Window **pwin, SDL_Renderer **prend)
{
    clear_stack();

    if (NULL != *prend)
        SDL_DestroyRenderer (*prend);
    if (NULL != *pwin)
        SDL_DestroyWindow (*pwin);
    SDL_Quit ();
}

int init_texture(SDL_Texture **ptext,SDL_Renderer *prend,int x,int y)
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

    stack_push(*ptext);

    return EXIT_SUCCESS;
}

void shuffle_fy (void* tb, size_t sizetb, size_t size)
{
    srand (time (NULL));
    unsigned char* ptr = tb;
    unsigned char temp[size];
    unsigned int j = 0;

    for (size_t i = sizetb - 1; i > 0; i--)
    {
        j = rand() % i;
        memcpy(temp,(ptr + (size * i)),size);
        memcpy((ptr + (size * i)),(ptr + (size * j)),size);
        memcpy((ptr + (size * j)),temp,size);
    }
    return;
}
