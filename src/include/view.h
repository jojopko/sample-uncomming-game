#ifndef _view_h_
#define _view_h_

#include <SDL2/SDL.h>
#include "struct.h"

void SetFocusToCell(char *focus, char m);

void ViewFocusCell(STCELL *cell, SDL_Surface *surf, SDL_Renderer *rend);

#endif