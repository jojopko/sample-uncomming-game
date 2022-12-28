#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../include/struct.h"
#include "../include/simplex-noise.h"
#include "../include/genmap.h"

#define SIMPLEX_NOISE open_simplex_noise3

#define FEATURE_SIZE  16
#define RANDOM_SEED   0
#define CHARSET_SIZE  26

int RandomInteger(int seed){
    int num, n1 = 0, n2 = 0, n3 = 0;
    n1 = seed >> 1;
    n2 = seed >> 3;
    n3 = seed << 2;
    num = n1 - n2 - n3;
    return num;
}

void GenerateBuild(UCHAR *builds){
    for(int i = 0; i < MAX_BUILD; i++){
        builds[i] = 45;
    }
}

void GenerateName(char *name){
    char *charset = "abcdefghijklmnopqrstuvwxyz";
    static uint iter = 0;
    uint rand_len = (uint)RandomInteger(time(NULL) + iter) % 16;

    if(rand_len < 3)
        rand_len = 3;

    for(int i = 0; i < rand_len; i++){
        int index = (uint)RandomInteger(i + iter + time(NULL)) % CHARSET_SIZE;
        name[i] = charset[index];
        iter += 1;
    }
}

double GetNoiseValue(ST_OSN_CONT *ctx, UCHAR octv_c, uint x, uint y){
    double value = .0;
    for(int i = 0; i < octv_c; i++){
        double v = .0;
        double fx = (double)x, fy = (double)y;
        if(i == 0){
            v = SIMPLEX_NOISE(ctx, fx / FEATURE_SIZE / 1,
                              fy / FEATURE_SIZE / 1, 0.0);
            v *= 1;
            v /= 7.0;
        } 
        else{
            v += SIMPLEX_NOISE(ctx, fx / FEATURE_SIZE / i * 2, 
                               fy / FEATURE_SIZE / i * 2, 0.0);
            v *= i*2;
            v /= 7.0;
        }
        value += v;
    }
    return value;
}

void GenerateBioms(UCHAR *biom_map, uint w, uint h, long int seed){
    ST_OSN_CONT *ctx;
    if(RANDOM_SEED)
        seed = time(NULL);

    open_simplex_noise(seed, &ctx);
    for(uint y = 0; y < h; y++){
        for(uint x = 0; x < w; x++){
            int index = y * w + x;
            double water_level = 1.3;
			double value = GetNoiseValue(ctx, 3, x, y);
            value += 0.5;

            if     (value < 0.10 * water_level)
                biom_map[index] = Ocean;
            else if(value < 0.20 * water_level)
                biom_map[index] = Sea;
            else if(value < 0.35 * water_level)
                biom_map[index] = Shallow;
            else if(value < 0.40 * water_level)
                biom_map[index] = Sand;
            else if(value < 0.55 * water_level)
                biom_map[index] = Dirt;
            else if(value < 0.80 * water_level)
                biom_map[index] = Forest;
            else if(value < 0.95 * water_level)
                biom_map[index] = Hills;
            else
                biom_map[index] = Mountains;
        }
    }
}
