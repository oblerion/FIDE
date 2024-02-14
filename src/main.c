#include "raylib.h"
#include "ui.h"
#include "fide.h"

int main(int npar,const char* lpar[])
{

    // Initialization
    //--------------------------------------------------------------------------------------
    // probl : data save uncomplete, make loading function for eatch data type
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 1000;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "FIDE ver 0.1");

    SetTargetFPS(30);   // Set our game to run at 60 frames-per-second
    struct FIDE fide = FIDE(40);
    FIDE_Load(&fide,"test.lua");
    puts("IDE is load");
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
            ClearBackground(BLUE);
            FIDE_Draw(&fide);
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL
    return 0;
}

