#ifndef _GEN_MAP_H_
#define _GEN_MAP_H_

#include "simplex-noise.h"
#include <sys/types.h>
#include "struct.h"

#define ST_OSN_CONT   struct osn_context

double GetNoiseValue(ST_OSN_CONT *ctx, UCHAR octv_c, uint x, uint y);
void   GenerateBioms(UCHAR *biom_map, uint w, uint h, long int seed);
void   GenerateName(char *name);
int    RandomNumber(int iter, int seed);
void   GenerateBuild(UCHAR *builds);

#endif