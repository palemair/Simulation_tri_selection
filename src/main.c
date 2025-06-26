#define _GNU_SOURCE
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sort.h"
#include "colors.h"
#include "../include/tpile.h"

/* parametres init */
static const char* wtitre = "Simulation tri selection";

static char help[] = "Simulation du tri par selection\n"
    "option n pour le nombre d'éléments à trier\n"
    "option s pour la taille de la fenêtre\n";

int main (int argc, char** argv)
{
    static int Nbelem = 15;
    static int Width_height = 650;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "hn:s:")) != -1)
        switch (c)
        {
        case 'n':
            Nbelem = strtol (optarg, NULL, 10);
            break;
        case 's':
            Width_height = strtol (optarg, NULL, 10);
            break;
        case 'h':
            fprintf (stderr, "%s", help);
            return EXIT_FAILURE;
            break;
        case '?':
            if (optopt == 'n')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default:
            abort ();
        }

    int statut = EXIT_FAILURE;
    SDL_bool continuer = SDL_TRUE;

    SDL_Window* window;
    SDL_Renderer* renderer;
    struct Graph Gr = {.w = Width_height,.h = Width_height,.nb = Nbelem };
    struct Graph* ptrGr = &Gr;

    init_graph (&window, &renderer, ptrGr, wtitre);
    init_pile ();

    SDL_Texture* textRed = NULL;
    SDL_Texture* textNavy = NULL;

    if (init_texture (&textRed, renderer, 10, 10))
        perror ("init_texture fails");

    if (init_texture (&textNavy, renderer, 10, 10))
        perror ("init_texture fails");

    empiler (textRed);
    empiler (textNavy);

    SDL_SetRenderTarget (renderer, textRed);
    clear_renderer (renderer, &Red);
    SDL_SetRenderTarget (renderer, NULL);

    SDL_SetRenderTarget (renderer, textNavy);
    clear_renderer (renderer, &Navy);
    SDL_SetRenderTarget (renderer, NULL);


    int data[ptrGr->nb];

    for (int i = 0; i < ptrGr->nb; i++)
    {
        data[i] = (3 * i + 5) % (ptrGr->h / 10);
    }

    SDL_Rect tbrec[ptrGr->nb];
    int indexmin, j, i;

    enum
    { INIT_0, REDRAW, CURRENT, SWAP };

    unsigned char STATE = INIT_0;

    unsigned int DLAY = 40;

    SDL_Event ev;

    while (continuer)
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
            switch (ev.key.keysym.sym)
            {
            case SDLK_SPACE:
                {
                    DLAY += 50;
                    break;
                }
            case SDLK_RETURN:
                {
                    if (DLAY > 50) DLAY -= 50;
                    break;
                }
            case SDLK_ESCAPE:
                {
                    continuer = SDL_FALSE;
                    break;
                }
            }
        }
        if (!continuer) break;

        switch (STATE)
        {
        case INIT_0:
            {
                shuffle_fy (data, sizeof data / sizeof data[0], sizeof data[0]);
                i = 0;
                j = 1;
                indexmin = 0; 
                STATE = REDRAW;
                break;
            }

        case REDRAW:
            {
                clear_renderer (renderer, &Silver);
                Draw (tbrec, data, i, renderer, &Blue, &Navy, ptrGr);
                SDL_RenderPresent (renderer);
                STATE = CURRENT;
                break;
            }
        case CURRENT:
            {
                if(j < ptrGr->nb)
                {
                    if (data[j] < data[indexmin]) indexmin = j;
                    SDL_RenderCopy (renderer, textNavy, NULL, &tbrec[j-1]);
                    SDL_RenderCopy (renderer, textRed, NULL, &tbrec[j]);
                    SDL_RenderPresent (renderer);
                    j++;
                }
                else
                {
                    STATE = SWAP;
                } 
                break;
            }

        case SWAP:
            {
                if ( i < ptrGr->nb-1)
                {
                    int temp = data[indexmin];
                    data[indexmin] = data[i];
                    data[i] = temp;
                    i++;
                    j=i+1;
                    STATE = REDRAW;
                }
                else
                {
                    STATE = INIT_0;
                }
                break;
            }
        }
        SDL_Delay (DLAY);
    }

    statut = EXIT_SUCCESS;

    while (!pile_empty ()) SDL_DestroyTexture (depiler ());

    destroy_graph (&window, &renderer);

    return statut;
}
