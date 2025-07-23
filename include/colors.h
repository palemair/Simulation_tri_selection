/* sort.c */
#ifndef _COLORS
#define _COLORS

#include <SDL2/SDL.h>

typedef struct color_pair {
    char name [21];
    uint8_t r,g,b;
} color_p;

/* prototypes */
void init_color_html(void);
int active_color(SDL_Renderer *rend, const SDL_Color *col, const int alpha);
int clear_renderer(SDL_Renderer *rend, const SDL_Color *col);

void update_colors(color_p *tb);
int set_SDL_Color(SDL_Color *const col, const char *str);

#endif
