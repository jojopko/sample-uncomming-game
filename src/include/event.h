#ifndef _event_h_
#define _event_h_

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

extern SDL_Event e;

void Events();
void Keyboard();
void Mouse();
void Sys();
void ScrollMap(int wy);

#endif