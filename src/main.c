#include "raylib.h"
#include "ide_menu.h"
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
    struct FIDE fide = FIDE(30);

    if(npar==2) FIDE_Load(&fide,lpar[1]);
    else  FIDE_Init(&fide);


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLUE);
        FIDE_Draw(&fide);
        switch(IDE_MENU_draw())
        {
            case MENU_open:

            break;
            case MENU_save:
                FIDE_Save(fide);
            break;
            case MENU_parameter:

            break;
            default:;
        }
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL
    FIDE_Free(&fide);
    return 0;
}

