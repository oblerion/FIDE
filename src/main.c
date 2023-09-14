#include "raylib.h"
#include "IDE.h"
int main(int npar,const char* lpar[])
{

    // Initialization
    //--------------------------------------------------------------------------------------
    // probl : data save uncomplete, make loading function for eatch data type
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 1000;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");


    SetTargetFPS(30);   // Set our game to run at 60 frames-per-second
    struct IDE side;
    if(npar==1)
        IDE_load(&side,"test.lua");
    else
        IDE_load(&side,lpar[1]);

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

    return 0;
}

