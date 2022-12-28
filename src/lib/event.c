#include "../include/event.h"
#include "../include/game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

SDL_Event e;
int speed_scroll = 2;

void Events(){
    SDL_WaitEvent(&e);
    Mouse();
    Keyboard();
    Sys();
}

void Mouse(){
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(e.type == SDL_MOUSEMOTION){
        fprintf(stderr, "[i] mouse: motion: x:%03d y:%03d\n", x, y);
    }
    if(e.type == SDL_MOUSEWHEEL){
        printf("[i] mouse: wheel: wheel.y:%d camera.*.w:%d camera.*.h:%d\n", 
                e.wheel.y, camera.viewport.w, camera.viewport.h);
        SDL_RenderClear(render);
        SDL_RenderCopy(render, terrmap, NULL, &camera.viewport);
    }
}

#if 0
void ScrollMap(int wy){
    int x, y;
    SDL_GetMouseState(&x, &y);
    // int camw = camera.viewport.w;
    // int camh = camera.viewport.h;
    // char inRange = !(camw > win_w / 2 || camh > win_h / 2) || (camw < win_w || camh < win_h);
    camera.viewport.w += speed_scroll * wy;
    camera.viewport.h += speed_scroll * wy;
    if(camera.viewport.x + (win_w / 2) > x)
        camera.viewport.x -= speed_scroll;
    if(camera.viewport.x + (win_w / 2) < x)
        camera.viewport.x += speed_scroll;
    if(camera.viewport.y + (win_h / 2) > y)
        camera.viewport.y -= speed_scroll;
    if(camera.viewport.y + (win_h / 2) < y)
        camera.viewport.y += speed_scroll;
}
#endif

void Keyboard(){
    if (e.type == SDL_KEYDOWN){
        fprintf(stderr, "[i] key pressed: {%s}\n", SDL_GetKeyName(e.key.keysym.sym));
    }
}

void Sys(){
    if(e.type == SDL_QUIT){
        printf("[i] Game is shutdown.\n");
        Exit();
    }
}