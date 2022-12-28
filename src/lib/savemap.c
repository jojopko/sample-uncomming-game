#include <stdio.h>
#include "../include/struct.h"

void DownloadMap(STCELL *map, char *path){
    
}

void SaveMap(STCELL *map, char *path, uint w, uint h){
    FILE *fp;
    path = "/home/gamerat/Desktop/game/src/build/saves/test.save";

    fp = fopen(path, "w");
    if(fp != NULL){
        fprintf(fp, "[%s]\n", path);
        fprintf(fp, "[%i:%i]\n", w, h);
        for(uint i = 0; i < w*h; i++){
            fprintf(fp, "%08i:%s:%03i:%s:%03i:%03i:%03i:%03i\n",
                    map[i].id, map[i].name, map[i].terr, map[i].builds,
                    map[i].product, map[i].adm, map[i].dip, map[i].mil);
        }
    }
    else{
        printf("\e[0;31m[!]\e[0m\t savemap: not found is \"%s\"\n", path);
    }
    fclose(fp);
}