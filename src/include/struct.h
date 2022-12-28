#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <stdlib.h>
#include <sys/types.h>

#define MAX_SAVE_NAME 64
#define MAX_NAME      16
#define MAX_BUILD     9

#define UCHAR         unsigned char
#define STCELL        struct Cell

struct Cell{
    uint  id;
    char  name[16];
    UCHAR terr;
    UCHAR builds[9];
    UCHAR product;
    UCHAR adm;
    UCHAR dip;
    UCHAR mil;
    char  focus;
};

struct Country{
    unsigned char id;
    unsigned char name; 
    int *provs;
    int cash;
    int man;
    unsigned char *boosts;
    unsigned char *war;
    unsigned char *aliance;
    unsigned char colour[4]; /* RGBA */
};

struct Unit{
    int position;
    unsigned char country;
    unsigned char type;
    int hp;
    int power;
};

enum biome{
    Ocean = 0, 
    Sea = 1, 
    Shallow = 2,
    Sand = 3,
    Dirt = 4,
    Forest = 5,
    Hills = 6,
    Mountains = 7,
    BiomSize
};

#endif