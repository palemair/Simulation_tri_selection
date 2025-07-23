#define _GNU_SOURCE
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "include/init_0.h"
#include "include/colors.h"
#include "include/drawing.h"

int main (int argc, char** argv)
{
    static const char* ConfigRep = "/usr/local/src/SDL/config/";
    char Filename[55];
    size_t len = strlen(ConfigRep);
    memcpy(Filename,ConfigRep,len);


    static const char* wtitre = "Simulation tri selection";

    static char help[] = "Simulation du tri par selection\n"
                         "option n pour le nombre d'éléments à trier\n"
                         "option s pour la taille de la fenêtre\n";

    static char Nbelem = 12;
    static int Width_height = 800;
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
            else if (optopt == 's')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default:
            abort ();
        }

    SDL_Window* window;
    SDL_Renderer* renderer;
    struct Graph Gr; 
    struct Graph* ptrGr = init_graph (&Gr, Width_height,Width_height,Nbelem);

    init_0 (&window, &renderer, ptrGr->w,ptrGr->h, wtitre);

    if(TTF_Init()==-1) 
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    char *font_curr = "Arial.ttf";
    size_t lenf = strlen(font_curr);
    memcpy(Filename+len,font_curr,lenf+1);
    /* fprintf (stderr, "%s\n", Filename); */

    /* TTF_Font* arial = TTF_OpenFont(Filename,14); */

    SDL_Color Silver,Red,Blue,Navy;
    set_SDL_Color (&Silver,"Silver");
    set_SDL_Color (&Red,"Red");
    set_SDL_Color (&Blue,"Blue");
    set_SDL_Color (&Navy,"Navy");

    SDL_Texture* textRed = NULL;
    SDL_Texture* textNavy = NULL;
    SDL_Texture* textSilver = NULL;

    init_texture (&textRed, renderer, 10, 10);
    init_texture (&textNavy, renderer, 10, 10);
    init_texture (&textSilver, renderer, 10, 10);

    SDL_SetRenderTarget (renderer, textRed);
    clear_renderer (renderer, &Red);
    SDL_SetRenderTarget (renderer, NULL);

    SDL_SetRenderTarget (renderer, textNavy);
    clear_renderer (renderer, &Navy);
    SDL_SetRenderTarget (renderer, NULL);

    SDL_SetRenderTarget (renderer, textSilver);
    clear_renderer (renderer, &Silver);
    SDL_SetRenderTarget (renderer, NULL);

    int data[ptrGr->nb];

    for (int i = 0; i < ptrGr->nb; i++)
    {
        data[i] = (3 * i + 5) % ((ptrGr->h / 2) + 12 * ptrGr->padding);
    }

    SDL_Rect tbrec[ptrGr->nb];
    int indexmin, j, i, cptblink;

    enum STATE_T
    { INIT_0, REDRAW, CURRENT, SWAP, BLINK, FINISH };

    int STATUS = EXIT_FAILURE;
    enum STATE_T STATE = INIT_0;
    int DLAY = 120;
    bool CONTINUE = true;


    SDL_Event ev;

    while (CONTINUE)
    {
        while (SDL_PollEvent (&ev))
        {
            switch (ev.type)
            {
            case SDL_WINDOWEVENT:
                if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    CONTINUE = false;
                }
                break;
            case SDL_KEYUP:
                switch (ev.key.keysym.sym)
                {
                case SDLK_SPACE:
                    {
                        DLAY += 40;
                        break;
                    }
                case SDLK_RETURN:
                    {
                        if (DLAY > 40) DLAY -= 40;
                        break;
                    }
                case SDLK_ESCAPE:
                    {
                        CONTINUE = false;
                        break;
                    }
                }
            }
        }

        if (!CONTINUE) break;

        switch (STATE)
        {
        case INIT_0:
            {
                shuffle_fy (data, sizeof data / sizeof data[0], sizeof data[0]);
                i = 0;
                STATE = REDRAW;
                break;
            }

        case REDRAW:
            {
                clear_renderer (renderer, &Silver);
                Draw (tbrec, data, i, renderer, &Blue, &Navy, ptrGr);
                indexmin = i;
                SDL_RenderCopy (renderer, textRed, NULL, &tbrec[i]);
                j = i + 1;
                STATE = CURRENT;
                break;
            }
        case CURRENT:
            {
                if (j < ptrGr->nb)
                {
                    indexmin = (data[j] < data[indexmin]) ? j : indexmin;
                    SDL_RenderCopy (renderer, textRed, NULL, &tbrec[j]);
                    if(j - 1 != i) SDL_RenderCopy (renderer, textNavy, NULL, &tbrec[j-1]);
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
                if (i < ptrGr->nb - 1)
                {
                    SDL_RenderCopy (renderer, textNavy, NULL, &tbrec[j-1]);
                    int temp = data[indexmin];

                    data[indexmin] = data[i];
                    data[i] = temp;
                    i++;
                    j = i;
                    cptblink = 4;
                    STATE = BLINK;
                }
                else
                {
                    j=0;
                    STATE = FINISH;
                }
                break;
            }

        case BLINK:
            {
                if (cptblink-- > 0)
                {
                    if (cptblink % 2 == 0) 
                    {
                        SDL_RenderCopy (renderer, textNavy, NULL, &tbrec[indexmin]);
                    }

                    else 
                    {
                        SDL_RenderCopy (renderer, textRed, NULL, &tbrec[indexmin]);
                    }
                }
                else
                {
                    STATE = REDRAW;
                }
                break;
            }
        case FINISH:
            {
                if (j < ptrGr->nb )
                {
                    SDL_RenderCopy (renderer, textNavy, NULL, &tbrec[j]);
                    j++;
                }
                else
                {
                    STATE = INIT_0;
                }
                break;
            }
        }
        SDL_RenderPresent (renderer);
        SDL_Delay (DLAY);
    }

    STATUS = EXIT_SUCCESS;
    TTF_Quit();
    destroy_0 (&window, &renderer);

    return STATUS;
}
