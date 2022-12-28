#ifndef _SAVE_MAP_H
#define _SAVE_MAP_H

#include <sys/types.h>
#include "struct.h"

void SaveMap(STCELL *map, char *name, uint w, uint h);

void DownloadMap(STCELL *map, char *path);

#endif