#ifndef _MAP_H_
#define _MAP_H_

#include <sys/types.h>
#include "struct.h"

extern int map_width, map_heigth;

void InitMap(STCELL *map, char *save_map);

#endif