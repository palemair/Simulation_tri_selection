#include <SDL2/SDL.h>
#include "../include/colors.h"

#define Size 140

static const char * txtcolorfile = "/usr/local/src/SDL/config/color.txt";
static const char * bincolorfile = "/usr/local/src/SDL/config/color.bin";
static color_p tbcolor[Size];

void init_color_html(void)
{
    FILE* inf = fopen(bincolorfile,"r");
    fread(tbcolor, sizeof(tbcolor[0]),Size,inf);
    fclose(inf);
    return;
}
int active_color (SDL_Renderer* rend, const SDL_Color* col, const int alpha)
{
    int x = (col->a * alpha) / 100;

    if (0 < SDL_SetRenderDrawColor (rend, col->r, col->g, col->b, x))
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

void update_colors(color_p *tb)
{
    FILE* inf = fopen(txtcolorfile,"r");
    int u = 0;
    int ret = 0;

    while ( ret != EOF)
    {
        ret = fscanf(inf,"%s %hhu %hhu %hhu",tbcolor[u].name,&tbcolor[u].r,&tbcolor[u].g,&tbcolor[u].b);
        u++;
    }
    fclose(inf);

    FILE* outf = fopen(bincolorfile, "wb");
    fwrite(tb, sizeof(tb[0]),Size,outf);
    fclose(outf);
}

static int searchB (const char *str) //Search color by name and return line number
{
    int index, test;
    size_t l = 0;
    size_t r = Size - 1;

    while(r >= l)
    {
        index = (l + r) / 2;
        char buffer[30];
        sscanf(str,"%s",buffer);
        test = strcmp(buffer,tbcolor[index].name);
    
        if (!test) return index;

        else if ( test < 0 ) r = index - 1;

        else if ( test > 0 ) l = index + 1;
    }
    return -1;
}

int set_SDL_Color(SDL_Color* const col, const char *colname)
{

    int res = searchB(colname);

    if(res == -1) 
    {
        fprintf(stderr,"%s\n","Not a color in table");
        return -1;
    }

    col->r = tbcolor[res].r;
    col->g = tbcolor[res].g;
    col->b = tbcolor[res].b;
    col->a = 255;

    return 0;
}
