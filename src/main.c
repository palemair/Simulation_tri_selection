#define _GNU_SOURCE
#include <SDL2/SDL.h>
/* #include <SDL2/SDL_ttf.h> */
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
            Nbelem = atoi (optarg);
            break;
        case 's':
            Width_height = atoi (optarg);
            break;
        case 'h':
            fprintf (stderr, "%s",help);
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

    unsigned int DLAY = 200;
    int statut = EXIT_FAILURE;
    SDL_bool continuer = SDL_TRUE;

    SDL_Window* window;
    SDL_Renderer* renderer;
    struct Graph Gr = {.w = Width_height,.h = Width_height,.nb = Nbelem };
    struct Graph* ptrGr = &Gr;

    init_graph (&window,&renderer,ptrGr,wtitre);
    init_pile();

    SDL_Texture *textRed = NULL;
    SDL_Texture *textNavy = NULL;
    
    if(init_texture(&textRed,renderer,10,10))
            perror("init_texture fails");

    if(init_texture(&textNavy,renderer,10,10))
            perror("init_texture fails");

    empiler(textRed);

    empiler(textNavy);
    
    SDL_SetRenderTarget (renderer, textRed);
    clear_renderer (renderer, &Red);
    SDL_SetRenderTarget (renderer, NULL);

    SDL_SetRenderTarget (renderer, textNavy);
    clear_renderer (renderer, &Navy);
    SDL_SetRenderTarget (renderer, NULL);

    /* if(TTF_Init() == -1){ */
	/* fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError()); */
	/* exit(EXIT_FAILURE); */
    /* } */

    /* TTF_Font* police = NULL; */


    int data[ptrGr->nb];

    for (int i = 0; i < ptrGr->nb; i++)
    {
        data[i] = (3 * i + 5) % (ptrGr->h / 10);
    }

    SDL_Rect tbrec[ptrGr->nb];

    SDL_Event ev;
    while (continuer)
    {
        shuffle_fy (data, sizeof data / sizeof data[0], sizeof data[0]);
        clear_renderer (renderer, &Silver);
        Draw (tbrec, data, 0, renderer, &Navy, &Navy, ptrGr);
        SDL_RenderPresent (renderer);
        SDL_Delay ((DLAY));

        int indexmin, j, i;

        for (i = 0; i < ptrGr->nb - 1; i++)
        {
            indexmin = i;

            SDL_RenderCopy (renderer, textRed, NULL, &tbrec[i]);
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
                        if (DLAY > 200) DLAY -= 100;
                        break;
                    }
                    if (ev.key.keysym.sym == SDLK_ESCAPE)
                    {
                        continuer = SDL_FALSE;
                        break;
                    }
                }

                if (!continuer) break;


                SDL_RenderCopy (renderer, textRed, NULL, &tbrec[j]);
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
                SDL_RenderCopy (renderer, textRed, NULL, &tbrec[indexmin]);
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

    while(!pile_empty()) SDL_DestroyTexture (depiler());

    destroy_graph(&window,&renderer);

    return statut;
}
