#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_keyboard.h>

#include "../include/map.h"
#include "../include/game.h"
#include "../include/event.h"
#include "../include/struct.h"
#include "../include/drawing.h"

int           isRun = 0;
int           tick;
int           win_w;
int           win_h;
int           win_x;
int           win_y;

SDL_Window   *mwin;
SDL_Surface  *winsurf;
SDL_Renderer *render;

SDL_Surface  *terrmap_s;
SDL_Surface  *gui_s;
SDL_Texture  *terrmap;
SDL_Texture  *gui;

STCELL       *gamemap;
struct Camera camera;

void Update(){
    tick = SDL_GetTicks();
    Events();

    // SDL_RenderPresent(render);
}

void Start(){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        fprintf(stderr, "[e] SDL init fail!\n");
        fprintf(stderr, "~ SDL message: %s\n", SDL_GetError());
    }

    win_x = 0;
    win_y = 0;

#if 1
    win_w = 480;
    win_h = 480;
#else
    win_w = 640;
    win_h = 512;
#endif

    mwin = SDL_CreateWindow("", 0, 0, win_w, win_h, 0);
    if(!mwin){
        fprintf(stderr, "[e] Window create fail!\n");
        fprintf(stderr, "~ SDL message: %s\n", SDL_GetError());
    }
    else{
        fprintf(stderr, "[i] window create.\n");
    }

    winsurf = SDL_GetWindowSurface(mwin);
    if(!winsurf){
        fprintf(stderr, "[e] Get window surface fail!\n");
        fprintf(stderr, "~ SDL message: %s\n", SDL_GetError());
    }
    else{
        fprintf(stderr, "[i] Window surface: width:%d heigth:%d\n", winsurf->w, winsurf->h);
    }

    render = SDL_CreateRenderer(mwin, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    if(!render){
        fprintf(stderr, "[e] Renderer create fail!\n");
        fprintf(stderr, "~ SDL message: %s\n", SDL_GetError());
    }

    PresentIMG("assets/gui/loading.png\0", render);

    SDL_Rect viewport = {0,0,win_w,win_h};
    camera.viewport = viewport;

    map_heigth = 64;
    map_width = 64;
    SDL_Rect cell = {0,0,1,1};
    gamemap = malloc(sizeof(STCELL) * map_width * map_heigth);
    InitMap(gamemap, "\0");

    int rm = 0xff000000, gm = 0x00ff0000, bm = 0x0000ff00, am = 0x000000ff;
    SDL_Surface *terrmap_s = SDL_CreateRGBSurface(0, map_width, map_heigth, 32, rm, gm, bm, am);
    SDL_Rect top_panel = {0,0,win_w, 64};
    SDL_Rect prov_panel = {0,top_panel.h,win_w/4, win_h-top_panel.h};
    SDL_Surface *gui_s = DrawGUI(&top_panel);
    // SDL_Surface *gui_s = DrawGUI(&prov_panel);


    DrawMap(gamemap, map_width, map_heigth, terrmap_s, &cell);
    terrmap = SDL_CreateTextureFromSurface(render, terrmap_s);
    gui     = SDL_CreateTextureFromSurface(render, gui_s);



    SDL_RenderClear(render);
    SDL_RenderCopy(render, terrmap, NULL, &camera.viewport);
    SDL_RenderCopy(render, gui, NULL, &camera.viewport);
    SDL_RenderPresent(render);
    isRun = 1;
}

void Exit(){
    isRun = 0;
    SDL_Quit();
}