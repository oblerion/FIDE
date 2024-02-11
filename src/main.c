#include "raylib.h"
#include "ide.h"
#include "ui.h"

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
    struct IDE side = IDE_init(npar,lpar);
    puts("IDE is load");
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        IDE_update(&side);
        BeginDrawing();
            ClearBackground(BLUE);
            IDE_draw(&side);
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL
    IDE_free(&side);
    return 0;
}

