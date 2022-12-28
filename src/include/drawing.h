#ifndef _drawing_h_
#define _drawing_h_

#include <SDL2/SDL_surface.h>
#include <sys/types.h>
#include "struct.h"
#include <SDL2/SDL.h>

SDL_Surface *LoadImg(char *file);
SDL_Surface *DrawGUI(SDL_Rect *aria);
char *GetNameBiom(UCHAR biom);
void DrawMap(STCELL *map, uint w, uint h, SDL_Surface *surf, SDL_Rect *cell);
void UpdateCell(STCELL *map, SDL_Surface *surf, SDL_Rect *cell, int id);
void AddCursor(int size, SDL_Surface *surf);
void PresentIMG(char *path, SDL_Renderer *render);
void DrawPanel(SDL_Surface *surf, SDL_Rect *aria);

#endif