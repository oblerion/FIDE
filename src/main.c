#include "raylib.h"
#include "IDE.h"
int main(int npar,char** lpar)
{

    // Initialization
    //--------------------------------------------------------------------------------------
    // probl : add/del itext
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 1000;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");


    SetTargetFPS(30);   // Set our game to run at 60 frames-per-second
    struct IDE side;
    if(npar==1)
        side = IDE_load("test.lua");
    else
        side = IDE_load(lpar[1]);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        IDE_update(&side);
        BeginDrawing();
            ClearBackground(BLUE);
            IDE_draw(&side);
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL

    return 0;
}

