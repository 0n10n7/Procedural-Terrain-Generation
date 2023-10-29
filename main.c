#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"
#include "terrainGen.c"

const int tileSize = 10;
const int cameraScrollSpeed = 5;

typedef struct Vector2 v2f;

typedef enum GameState
{
    STATE_MENU,
    STATE_GAME,
    STATE_SPELLBOOK,
    STATE_GAMEOVER
} GameState;
typedef enum View
{
    LAND_WATER,
    TECTONICPLATES,
    CURRENTS,
    ELEVATION,
    LAST
} View;


int main()
{
    GameState gameState = STATE_MENU;
    View view = LAND_WATER;
    time_t t;
    int cameraViewX = 0;
    int cameraViewY = 0;
    srand((unsigned)time(&t));

    // ----------------
    // DISPLAY SETTINGS
    // ----------------
    // 1120,1280 är *5
    //v2f windowSize = {1120, 1286};
    // v2f windowSize = {560, 606};
     v2f windowSize = {1440, 900};
    // v2f windowSize = {2560, 1440};
    InitWindow(windowSize.x, windowSize.y, "ProceduralTerrainGen");
    ToggleFullscreen();

    // Initialize inputs
    bool eDown =false;
    bool wDown =false;
    bool aDown =false;
    bool sDown =false;
    bool dDown =false;
    bool executePressed = false;

    TerrainGenerator();

    while (!WindowShouldClose())
    {
        switch (gameState)
        {
        case STATE_MENU:
        {
            executePressed = IsKeyPressed(KEY_DOWN);
            eDown = IsKeyPressed(KEY_E);
            BeginDrawing();
            ClearBackground(GRAY);
            DrawText("press down to continue",20,20,40,(Color){200,200,255,255});
            EndDrawing();
            if(executePressed){
                gameState = STATE_GAME;
            }
            else if(eDown){
                gameState = STATE_SPELLBOOK;
            }
        }
        break;
        case STATE_GAME:
        {
            executePressed = IsKeyPressed(KEY_DOWN);
            eDown = IsKeyPressed(KEY_E);

            wDown = IsKeyDown(KEY_W);
            aDown = IsKeyDown(KEY_A);
            sDown = IsKeyDown(KEY_S);
            dDown = IsKeyDown(KEY_D);
            bool water = true;
            if(executePressed){
                TerrainGenerator();
            }
            if(eDown){
                if(view<LAST){
                    view++;
                }
                else{
                    view=0;
                }
            }
            if(wDown){
                cameraViewY-= cameraScrollSpeed;
            }
            if(aDown){
                cameraViewX-= cameraScrollSpeed;
            }
            if(sDown){
                cameraViewY+= cameraScrollSpeed;
            }
            if(dDown){
                cameraViewX+= cameraScrollSpeed;
            }
            // ------
            // RENDER
            // ------
            BeginDrawing();
            ClearBackground(BLACK);
            switch (view)
                    {
                    case TECTONICPLATES:
                        for (int x = 0; x < worldSize; x++)
                        {
                            for (int y = 0; y < worldSize; y++)
                            {
                                //DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, (Color){10 *(map.tectonicsplates.grid[x][y]%11) + 70 , 50 * (map.tectonicsplates.grid[x][y]%5), 70 * (map.tectonicsplates.grid[x][y]%3), 255});
                                DrawPixel((x)-cameraViewX, (y ) -cameraViewY, (Color){10 *(map.tectonicsplates.grid[x][y]%11) + 70 , 50 * (map.tectonicsplates.grid[x][y]%5), 70 * (map.tectonicsplates.grid[x][y]%3), 255});
                            }
                                
                        }
                    break;
                    
                    case LAND_WATER:
                    for (int x = 0; x < worldSize; x++)
                        {
                            for (int y = 0; y < worldSize; y++)
                            {
                                switch (map.data[x][y][LAND_WATER_MOUNTAIN])
                                {
                                case TILE_TYPE_WATER:
                                    //DrawRectangle((x * tileSize)-cameraViewX, (y * tileSize) -cameraViewY, tileSize, tileSize, (Color){15 * (map.tectonicsplates.grid[x][y]%3), 25 * (map.tectonicsplates.grid[x][y]%4 +1), 175 + 25 * (map.tectonicsplates.grid[x][y]%3), 255});
                                    DrawPixel((x)-cameraViewX, (y ) -cameraViewY, (Color){15 * (map.tectonicsplates.grid[x][y]%3), 25 * (map.tectonicsplates.grid[x][y]%4 +1), 175 + 25 * (map.tectonicsplates.grid[x][y]%3), 255});
                                    break;
                                case TILE_TYPE_LAND:
                                    //DrawRectangle((x * tileSize)-cameraViewX, (y * tileSize) -cameraViewY, tileSize, tileSize, (Color){15 * (map.tectonicsplates.grid[x][y]%3) + 120 , 25 * (map.tectonicsplates.grid[x][y]%5) + 100, 25, 255});
                                    DrawPixel((x)-cameraViewX, (y ) -cameraViewY, (Color){15 * (map.tectonicsplates.grid[x][y]%3) + 120 , 25 * (map.tectonicsplates.grid[x][y]%5) + 100, 25, 255});
                                    break;
                                case TILE_TYPE_MOUNTAIN:
                                    /* code */
                                    break;
                                
                                default:
                                    break;
                                }
                            }
                                
                        }
                        
                        break;
                    case ELEVATION:
                        for (int x = 0; x < worldSize; x++)
                        {
                            for (int y = 0; y < worldSize; y++)
                            {
                                DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, (Color){255 / (255/map.elevation[x][y]), 255 / (255/map.elevation[x][y]), 255 / (255/map.elevation[x][y]), 255});
                            }
                        }
                        break;
                    default:
                        //DrawText(TextFormat("%d",map.tectonicsplates.grid[x][y]),x * tileSize, y * tileSize,3,(Color){0,0,0,255});
                    
                        //Köppen

                        //DrawText(map.tectonicsplates.grid[x][y],x*tileSize,y*tileSize,11,(Color){200,200,255,255});
                        // switch (map.data[x][y][KOPPEN])
                        // {
                        // case TILE_TYPE_AF:
                        //     DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, (Color){0, 0, 255, 255});
                        //     puts("One Koppen AF comming right up");
                        // default:
                        //     break;
                        // }
                        break;
                    }
            
            // for(int i = 0 ; i < tectonicsCount; i++){
            //     DrawRectangle(map.tectonicsplates.centersX[i] * tileSize, map.tectonicsplates.centersY[i] * tileSize, tileSize, tileSize, (Color){0, 0, 255, 255});
            // }
            DrawFPS(20,20);
            EndDrawing();
        }
        break;
        case STATE_SPELLBOOK:
        {
            executePressed = IsKeyPressed(KEY_DOWN);
            BeginDrawing();
            ClearBackground(BLACK);
            EndDrawing();
            if(executePressed){
                gameState = STATE_GAME;
            }
        }
        break;
        case STATE_GAMEOVER:
        {
            
            BeginDrawing();
            ClearBackground(BLACK);
            EndDrawing();
        }
        break;

        default:
            break;
        }
    }
    CloseWindow();
    return 0;
}