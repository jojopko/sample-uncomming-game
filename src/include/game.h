#ifndef _game_h_
#define _game_h_

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "struct.h"

struct Camera{
    SDL_Rect viewport;
};

extern int isRun;
extern int tick;
extern STCELL *gamemap;

extern SDL_Window *mwin;
extern SDL_Surface *winsurf;
extern SDL_Renderer *render;

extern SDL_Surface  *terrmap_s;
extern SDL_Surface  *gui_s;
extern SDL_Texture  *terrmap;
extern SDL_Texture  *gui;

extern SDL_Texture *geomap;
extern struct Camera camera;
extern int win_w;
extern int win_h;
extern int win_x;
extern int win_y;

void Update();
void Start();
void Exit();

#endif