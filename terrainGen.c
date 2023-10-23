#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"


const int worldSize = 1440;
const int amountOfTectonics = 12+8;
const int weightRange = 2;

typedef enum TileTypeIndex
{
    EMPTY_OR_MOUNTAIN,
    KOPPEN,
    WATER_CURRENT,
    WIND_CURRENT,
    RAIN_SHADOW,
    CURRENT_TEMP,
    INDEX_LENGTH,
} TileTypeIndex;

typedef enum TileType
{
    TILE_TYPE_LAND,
    TILE_TYPE_MOUNTAIN,
    TILE_TYPE_WATER,
    TILE_TYPE_RAIN_SHADOW,
    TILE_TYPE_WARM_CURRENT,
    TILE_TYPE_COLD,CURRENT,
    TILE_TYPE_NORTH_WIND_CURRENT,
    TILE_TYPE_EAST_WIND_CURRENT,
    TILE_TYPE_SOUTH_WIND_CURRENT,
    TILE_TYPE_WEST_WIND_CURRENT,
    TILE_TYPE_NORTH_WATER_CURRENT,
    TILE_TYPE_EAST_WATER_CURRENT,
    TILE_TYPE_SOUTH_WATER_CURRENT,
    TILE_TYPE_WEST_WATER_CURRENT,
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
    TILE_TYPE_EF,
    TILE_TYPE_NULL = -1
} TileType;

typedef enum Directions
{
    NORTH,
    EAST,
    SOUTH,
    WEST,
} Directions;

typedef struct Tectonicplates{
    int grid [worldSize][worldSize];
    bool water[amountOfTectonics];
}Tectonicplates;

typedef struct Terrain
{
    TileType data[worldSize][worldSize][INDEX_LENGTH];
    int elevation[worldSize][worldSize];
    Tectonicplates tectonicsplates;
}Terrain;

Terrain map;

//Creates tectonic plates, tectonics count should be smaller than world size by a large margin
Tectonicplates TectonicplatesCreator(int tectonicsCount){
    Tectonicplates tectonicsplate;
    int indexX [tectonicsCount];
    int indexY [tectonicsCount];
    float indexWeight[tectonicsCount];
    for(int i = 0; i < worldSize; i ++){
        for(int j = 0; j < worldSize; j ++){
            tectonicsplate.grid[j][i] = 0;
        }
    }
    for(int i = 0; i < tectonicsCount; i ++){
        tectonicsplate.water[i]=false;
        indexWeight[i] = weightRange+0.5;

        indexX[i]=rand() % worldSize;
        indexY[i]=rand() % worldSize;
        switch (i)
        {
        case NORTH:
            indexY[i]=0;
            indexX[i]=worldSize/2;
            break;
        case EAST:
            indexX[i]=worldSize-1;
            indexY[i]=worldSize/2;
            break;
        case SOUTH:
            indexY[i]=worldSize-1;
            indexX[i]=worldSize/2;
            break;
        case WEST:
            indexX[i]=0;
            indexY[i]=worldSize/2;
            break;
        case NORTH+4:
            indexY[i]=rand()%(int)(worldSize/2) + 50;
            break;
        case EAST+4:
            indexX[i]= worldSize - (rand()%(int)(worldSize/2) + 50);
            break;
        case SOUTH+4:
            indexY[i]= worldSize - (rand()%(int)(worldSize/2) + 50);
            break;
        case WEST+4:
            indexX[i]=rand()%(int)(worldSize/2) + 50;
            break;
        default:
            indexWeight[i] = ((float)(rand()%1000000 ))/1000000 +weightRange;
            break;
        }
        
        tectonicsplate.grid[indexX[i]][indexY[i]]=i;
    }
    for (int i = 0; i < worldSize; i++)
    {
        for(int j = 0; j < worldSize; j ++){
            //Intenitonally long variabel name because i find it funny
            float manhatanDistanceToNearestTectonicplateWeighted = worldSize*10;
            float vectorDistanceWeighted = worldSize*10;
            int indexForNearestTectonicplate=-1;
            for(int k = 0; k < tectonicsCount; k ++)
            {
                float tempDistance = (abs(j-indexX[k]) + abs(i-indexY[k]));
                tempDistance *= indexWeight[k];
                //printf("Weight %d is %f, temp distance is %f\n",k,indexWeight[k],tempDistance);
                if(tempDistance < 0){
                    tempDistance *= -1;
                }
                if(tempDistance < manhatanDistanceToNearestTectonicplateWeighted)
                {
                    manhatanDistanceToNearestTectonicplateWeighted = tempDistance;
                    indexForNearestTectonicplate = k;
                }
            }
            tectonicsplate.grid[j][i] = tectonicsplate.grid[indexX[indexForNearestTectonicplate]][indexY[indexForNearestTectonicplate]];
            if(i == 0 || i == worldSize-1 || j == 0 || j == worldSize-1){
                tectonicsplate.water[indexForNearestTectonicplate] = true;
            }
        }
    }
    
    for(int i = 0; i <= tectonicsCount; i ++){
    }
    return tectonicsplate;
}

void TerrainGenerator(){
    map;
    for (int i = 0; i < worldSize; i++)
    {
        for(int j = 0; j < worldSize; j ++){
            map.data[j][i][0]=TILE_TYPE_WATER;
        }
    }
    map.tectonicsplates = TectonicplatesCreator(amountOfTectonics);
}
