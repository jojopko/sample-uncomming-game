#include <stdio.h>
#include "../include/struct.h"
#include "../include/genmap.h"

int map_width, map_heigth;

void InitMap(STCELL *map, char *save_name){
    UCHAR *biom_map = malloc(map_width*map_heigth*sizeof(UCHAR));
    GenerateBioms(biom_map, map_width, map_heigth, 1000);
    for(int i = 0; i < map_width * map_heigth; i++){
        map[i].id = i;
        GenerateName(map[i].name);
        map[i].terr = biom_map[i];
        GenerateBuild(map[i].builds);
        map[i].product = 0;
        map[i].adm = 1;
        map[i].dip = 1;
        map[i].mil = 1;
        map[i].focus = 0;
    }
    fprintf(stderr, "[i] map.c:InitMap() - OK. {%p}\n", &map);
    free(biom_map);
}
