#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"
#include "terrainGen.c"

const int tileSize = 5;

typedef struct Vector2 v2f;

typedef enum GameState
{
    STATE_MENU,
    STATE_GAME,
    STATE_SPELLBOOK,
    STATE_GAMEOVER
} GameState;

int main()
{
    GameState gameState = STATE_MENU;
    time_t t;
    srand((unsigned)time(&t));

    // ----------------
    // DISPLAY SETTINGS
    // ----------------
    // 1120,1280 är *5
    v2f windowSize = {1120, 1286};
    // v2f windowSize = {560, 606};
    // v2f windowSize = {1440, 900};
    // v2f windowSize = {2560, 1440};
    InitWindow(windowSize.x, windowSize.y, "SpellJam");
    //ToggleFullscreen();
    // SetTargetFPS(10);

    // Load textures
    Texture2D worldSprites = LoadTexture("Assets/world.png");

    // Initialize inputs
    bool upDown = false;
    bool downDown = false;
    bool leftDown = false;
    bool rightDown = false;
    bool eDown =false;
    bool squarePressed = false;
    bool trianglePressed = false;
    bool circlePressed = false;
    bool executePressed = false;

    

    while (!WindowShouldClose())
    {
        switch (gameState)
        {
        case STATE_MENU:
        {
            executePressed = IsKeyPressed(KEY_DOWN);
            eDown = IsKeyPressed(KEY_E);
            BeginDrawing();
            ClearBackground(BLACK);
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
            
            // ------
            // RENDER
            // ------
            BeginDrawing();
            ClearBackground(BLACK);

            
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