#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "colors.h"

/* parametres init */
static unsigned int Width_height = 650;
static unsigned int Nbelem = 15;

int main (int argc, char** argv)
{
static const char* wtitre = "Simulation tri selection";
    switch (argc)
    {
    case 2:
        {
            sscanf (argv[1], "%u", &Width_height);
            break;
        }

    case 3:
        {
            sscanf (argv[1], "%u", &Width_height);
            sscanf (argv[2], "%u", &Nbelem);
            break;
        }

    default:
        {
            break;
        }
    }

    unsigned int DLAY = 200;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_bool continuer = SDL_TRUE;
    int statut = EXIT_FAILURE;

    struct Graph Gr = {.w = Width_height,.h = Width_height,.nb = Nbelem };
    struct Graph* ptrGr = &Gr;

    init_graph (ptrGr);

    if (0 != SDL_Init (SDL_INIT_VIDEO))
    {
        fprintf (stderr, "Erreur SDL_Init : %s", SDL_GetError ());
        SDL_Quit ();
        return EXIT_FAILURE;
    }

    if (0 !=
        SDL_CreateWindowAndRenderer (Gr.w, Gr.h, SDL_WINDOW_SHOWN, &window, &renderer))
    {
        fprintf (stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError ());
        if (NULL != renderer)
            SDL_DestroyRenderer (renderer);
        if (NULL != window)
            SDL_DestroyWindow (window);
        SDL_Quit ();
        return EXIT_FAILURE;
    }
    SDL_SetWindowTitle(window,wtitre);

    SDL_Texture* textred =
        SDL_CreateTexture (renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                           50, 50);
    if (NULL == textred)
    {
        fprintf (stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError ());
        if (NULL != renderer)
            SDL_DestroyRenderer (renderer);
        if (NULL != window)
            SDL_DestroyWindow (window);
        SDL_Quit ();
        return EXIT_FAILURE;
    }

    SDL_Texture* textNavy =
        SDL_CreateTexture (renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                           50, 50);
    if (NULL == textNavy)
    {
        fprintf (stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError ());
        if (NULL != textred)
            SDL_DestroyTexture (textred);
        if (NULL != renderer)
            SDL_DestroyRenderer (renderer);
        if (NULL != window)
            SDL_DestroyWindow (window);
        SDL_Quit ();
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget (renderer, textred);
    clear_renderer (renderer, &Red);
    SDL_SetRenderTarget (renderer, NULL);

    SDL_SetRenderTarget (renderer, textNavy);
    clear_renderer (renderer, &Navy);
    SDL_SetRenderTarget (renderer, NULL);

    SDL_Event ev;

    int data[ptrGr->nb];

    for (int i = 0; i < ptrGr->nb; i++)
    {
        data[i] = (3 * i + 8) % (ptrGr->h / 10);
    }

    SDL_Rect tbrec[ptrGr->nb];

    while (continuer)
    {
        shuffle_fy (data, sizeof data / sizeof data[0], sizeof data[0]);
        clear_renderer (renderer, &Silver);
        Draw (tbrec, data, 0, renderer, &Navy, &Navy, ptrGr);
        SDL_RenderPresent (renderer);
        SDL_Delay ((2 * DLAY));

        int indexmin, j, i;

        for (i = 0; i < ptrGr->nb - 1; i++)
        {
            indexmin = i;

            SDL_RenderCopy (renderer, textred, NULL, &tbrec[i]);
            SDL_RenderPresent (renderer);
            SDL_Delay (DLAY);

            SDL_RenderCopy (renderer, textNavy, NULL, &tbrec[i]);
            SDL_RenderPresent (renderer);
            SDL_Delay (DLAY);

            SDL_RenderCopy (renderer, textred, NULL, &tbrec[i]);
            SDL_RenderPresent (renderer);
            SDL_Delay (DLAY);

            for (j = i + 1; j < ptrGr->nb; j++)
            {
                SDL_PollEvent (&ev);

                switch (ev.type)
                {
                case SDL_WINDOWEVENT:
                    if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
                    {
                        continuer = SDL_FALSE;
                    }
                    break;
                case SDL_KEYUP:
                    if (ev.key.keysym.sym == SDLK_SPACE)
                    {
                        DLAY += 100;
                        break;
                    }
                    if (ev.key.keysym.sym == SDLK_RETURN)
                    {
                        if (DLAY > 100) DLAY -= 100;
                        break;
                    }
                    if (ev.key.keysym.sym == SDLK_ESCAPE)
                    {
                        continuer = SDL_FALSE;
                        break;
                    }
                }

                if (!continuer) break;


                SDL_RenderCopy (renderer, textred, NULL, &tbrec[j]);
                SDL_RenderPresent (renderer);
                SDL_Delay ((DLAY / 5));

                SDL_RenderCopy (renderer, textNavy, NULL, &tbrec[j]);
                SDL_RenderPresent (renderer);
                SDL_Delay ((DLAY / 5));

                if (data[j] < data[indexmin]) indexmin = j;
            }

            if (!continuer) break;

            for (int t = 0; t < 2; t++)
            {
                SDL_RenderCopy (renderer, textred, NULL, &tbrec[indexmin]);
                SDL_RenderPresent (renderer);
                SDL_Delay (DLAY);

                SDL_RenderCopy (renderer, textNavy, NULL, &tbrec[indexmin]);
                SDL_RenderPresent (renderer);
                SDL_Delay (DLAY);
            }

            int temp = data[indexmin];

            data[indexmin] = data[i];
            data[i] = temp;

            clear_renderer (renderer, &Silver);
            Draw (tbrec, data, i, renderer, &Navy, &Blue, ptrGr);
            SDL_RenderPresent (renderer);
            SDL_Delay (DLAY);
        }

        if (!continuer) break;

        clear_renderer (renderer, &Silver);
        Draw (tbrec, data, i, renderer, &Navy, &Blue, ptrGr);
        SDL_RenderPresent (renderer);
        SDL_Delay (2 * DLAY);
    }

    statut = EXIT_SUCCESS;
    goto Quit;

  Quit:
    if (NULL != textNavy)
        SDL_DestroyTexture (textNavy);
    if (NULL != textred)
        SDL_DestroyTexture (textred);
    if (NULL != renderer)
        SDL_DestroyRenderer (renderer);
    if (NULL != window)
        SDL_DestroyWindow (window);
    SDL_Quit ();
    return statut;
}
