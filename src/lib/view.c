#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/struct.h"
#include "../include/drawing.h"
#include "../include/mathtools.h"

// static char *_before = NULL;

void drawText(SDL_Surface* screen, char* string,
              int size, int x, int y,
              int fR, int fG, int fB){
    SDL_Rect textLocation = { x, y, 0, 0 };
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("/home/gamerat/Desktop/game/src/build/assets/fonts/source_code/Black.ttf", size);
    if (!font)
        printf("%s\n", TTF_GetError());
    SDL_Color foreground = { fR, fG, fB };
    TTF_SizeUNICODE(font, (Uint16*)string, &textLocation.w, &textLocation.h);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, string, foreground);

    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    TTF_Quit();
}

void SetFocusToCell(char *focus, char m){
    // if(_before != NULL)
    //     *_before = 0;
    // _before = focus;
    *focus = m;
    fprintf(stderr, "[i] view.c:SetFocusToCell() - OK. {%d}\n", *focus);
}

void ViewFocusCell(STCELL *cell, SDL_Surface *surf, SDL_Renderer *rend){
    SDL_Rect area = {0,0,1,surf->h};
    for(int xpos = 0; xpos < (surf->w); xpos++){
        SDL_Surface *img;
        if(xpos == 0 || xpos == (surf->w)-1)
            img = LoadImg("assets/gui/block/padding.png\0");
        else
            img = LoadImg("assets/gui/block/content.png\0");
        if(SDL_BlitScaled(img, NULL, surf, &area))
            fprintf(stderr, "[e] view.c:ViewFocusCell() - scaled fail! {%p}\n", img);
        SDL_FreeSurface(img);
        area.x++;
    }
    char name[16];
    numtostr(cell->id, name);
    drawText(surf, name, 16, 0, 0, 255, 255, 255);
    fprintf(stderr, "[i] view.c:ViewFocusCell() - OK.\n");
}