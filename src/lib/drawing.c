#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string.h>
#include <sys/cdefs.h>

#include "../include/struct.h"
#include "../include/drawing.h"
#include "../include/game.h"

void PresentIMG(char *path, SDL_Renderer *render){
    SDL_Surface *loadgames = LoadImg(path);
    SDL_Texture *loadgamet = SDL_CreateTextureFromSurface(render, loadgames);
    SDL_RenderCopy(render, loadgamet, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_FreeSurface(loadgames);
    SDL_DestroyTexture(loadgamet);
}

char *GetNameBiom(UCHAR biom){
    if(biom == Ocean)
        return "assets/biom/ocean.png\0";
    else if(biom == Sea)
        return "assets/biom/sea.png\0";
    else if(biom == Shallow)
        return "assets/biom/shallow.png\0";
    else if(biom == Sand)
        return "assets/biom/sand.png\0";
    else if(biom == Dirt)
        return "assets/biom/dirt.png\0";
    else if(biom == Forest)
        return "assets/biom/forest.png\0";
    else if(biom == Hills)
        return "assets/biom/hills.png\0";
    else if(biom == Mountains)
        return "assets/biom/mountains.png\0";
    else 
        return NULL;
}

SDL_Surface *LoadImg(char *file){
    char path[256], *dir;
    int path_s, file_s, dir_s;

    IMG_Init(IMG_INIT_PNG);
    /* Get path */
    dir  = SDL_GetBasePath();
    path_s = 0, dir_s = 0, file_s = 0;
    while(dir[dir_s++]){;}
    while(file[file_s++]){;}
    for(int i = 0; i < dir_s; i++)
        path[path_s++] = dir[i];
    path_s--;
    for(int i = 0; i < file_s; i++)
        path[path_s++] = file[i];
    path[path_s] = '\0';

    SDL_Surface *img = IMG_Load(path);
    IMG_Quit();
    return img;
}

void DrawMap(STCELL *map, uint w, uint h, SDL_Surface *surf, SDL_Rect *cell){
    SDL_Rect rect = {0,0,cell->h,cell->w};
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            int index = w * y + x;
            char *file = GetNameBiom(map[index].terr);
            SDL_Surface *img = LoadImg(file);
            if(img == NULL)
                printf("[e] drawing.c:DrawMap() - image fail! {%p}\n", img);
            if(SDL_BlitScaled(img, NULL, surf, &rect))
                fprintf(stderr, "[e] drawing.c:DrawMap() - scaled fail! {%p}\n", surf);
            SDL_FreeSurface(img);
            rect.x += rect.w;
        }
        rect.y += rect.h;
        rect.x = 0;
    }
    fprintf(stderr, "[i] drawing.c:DrawMap() - OK.\n");
}

void UpdateCell(STCELL *map, SDL_Surface *surf, SDL_Rect *cell, int id){
    char *path;
    path = GetNameBiom(map[id].terr);
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface *img = IMG_Load(path);
    SDL_BlitScaled(img, NULL, surf, cell);
    SDL_FreeSurface(img);
    IMG_Quit();
    fprintf(stderr, "[i] drawing.c:UpdateCell() - OK.\n");
}

void AddCursor(int size, SDL_Surface *surf){
    SDL_Cursor *cursor = SDL_CreateColorCursor(surf, size/2, size/2);
    SDL_SetCursor(cursor);
    SDL_ShowCursor(SDL_ENABLE);
}

void DrawCellInfo(SDL_Surface *surf, STCELL *cell){
    //
}

void DrawPanel(SDL_Surface *surf, SDL_Rect *aria){
    SDL_Rect draw_pos;
    draw_pos.x = aria->x;
    draw_pos.y = aria->y;
    draw_pos.w = 1;
    draw_pos.h = 1;

    while(draw_pos.y < aria->h){
        draw_pos.x = aria->x;
        while(draw_pos.x < aria->w){
            int is_border = (draw_pos.x == aria->x) || (draw_pos.x == aria->w -1) ||
                            (draw_pos.y == aria->y) || (draw_pos.y == aria->h-1);
            
            if(is_border){
                SDL_Surface *img = LoadImg("assets/gui/border.png\0");
                if(SDL_BlitScaled(img, NULL, surf, &draw_pos)){
                    fprintf(stderr, "[e] drawing.c:DrawPanel()\n");
                    fprintf(stderr, "~ SDL message: %s\n", SDL_GetError());
                }
            }
            else{
                SDL_Surface *img = LoadImg("assets/gui/content.png\0");
                if(SDL_BlitScaled(img, NULL, surf, &draw_pos)){
                    fprintf(stderr, "[e] drawing.c:DrawPanel()\n");
                    fprintf(stderr, "~ SDL message: %s\n", SDL_GetError());
                }
            }
            draw_pos.x++;
        }
        draw_pos.y++;
    }
}

SDL_Surface *DrawGUI(SDL_Rect *aria){
    int w, h;
    int rm = 0xff000000, 
        gm = 0x00ff0000, 
        bm = 0x0000ff00, 
        am = 0x000000ff;

    SDL_GetWindowSize(mwin, &w, &h);
    SDL_Surface *surf = SDL_CreateRGBSurface(0, w, h, 32, rm, gm, bm, am);
    DrawPanel(surf, aria);
    return surf;
}