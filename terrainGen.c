#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"

const int worldSize = 100;

typedef enum TileType
{
    TILE_TYPE_EMPTY,
    TILE_TYPE_MOUNTAIN,
    TILE_TYPE_RAIN_SHADOW,
    TILE_TYPE_WARM_CURRENT,
    TILE_TYPE_COLD,CURRENT,
    TILE_TYPE_AF,
    TILE_TYPE_AM,
    TILE_TYPE_AW_AS,
    TILE_TYPE_BWH,
    TILE_TYPE_BWK,
    TILE_TYPE_BSH,
    TILE_TYPE_BSK,
    TILE_TYPE_CSA,
    TILE_TYPE_CSB,
    TILE_TYPE_CSC,
    TILE_TYPE_CWA,
    TILE_TYPE_CWB,
    TILE_TYPE_CWC,
    TILE_TYPE_CFA,
    TILE_TYPE_CFB,
    TILE_TYPE_CFC,
    TILE_TYPE_DSA,
    TILE_TYPE_DSB,
    TILE_TYPE_DSC,
    TILE_TYPE_DSD,
    TILE_TYPE_DWA,
    TILE_TYPE_DWB,
    TILE_TYPE_DWC,
    TILE_TYPE_DWD,
    TILE_TYPE_DFA,
    TILE_TYPE_DFB,
    TILE_TYPE_DFD,
    TILE_TYPE_ET,
    TILE_TYPE_EF
} TileType;

typedef struct Terrain
{
    TileType data[worldSize][worldSize][2];
    int elevation[worldSize][worldSize][1];
}Terrain;

typedef struct Tectonicplates{

}Tectonicplates;
typedef struct Currents{

}Currents;

//Creates tectonic plates, tectonics count should be smaller than world size by a large margin
Tectonicplates TectonicplatesCreator(int tectonicsCount){
    int grid [worldSize][worldSize] = {0};
    int indexX [tectonicsCount];
    int indexY [tectonicsCount];
    int indexWeight[tectonicsCount];
    for(int i = 0; i < tectonicsCount; i ++){
        indexX[i]=rand() % worldSize;
        indexY[i]=rand() % worldSize;
        indexWeight[i]=rand() % 11;
        grid[indexX[i]][indexY[i]]=i;
    }
}

Terrain TerrainGenerator(){
    Terrain terrain;
    for (int i = 0; i < worldSize; i++)
    {
        for(int j = 0; j < worldSize; j ++){
            terrain.data[j][i][0]=TILE_TYPE_EMPTY;
        }
    }
    
}
