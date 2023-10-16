#include "ide_menu.h"
#define MAX_SIZE 3
const char BTN_NAME[MAX_SIZE][15] = 
{
    "[o]pen",
    "[s]ave",
    "[p]arameter"
};

struct IDE_MENU IDE_MENU()
{
    struct IDE_MENU uimenu;
    uimenu.visible=0;
    return uimenu;
}

IDE_MENU_ID IDE_MENU_draw(struct IDE_MENU* uimenu)
{
    int ret=MENU_default;
    if(IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
    {
        uimenu->visible=true;
    }
    else uimenu->visible=false;

    if(uimenu->visible)
    {
        if(IsKeyPressed(KEY_O)) 
        {
            ret=MENU_open;
        }
        else if(IsKeyPressed(KEY_S))
        {
            ret=MENU_save;
        }
        else if(IsKeyPressed(KEY_P))
        {
            ret=MENU_parameter;
        }
        const int size = 24;
        DrawRectangle(2,2,4*size,MAX_SIZE*size,BLUE);
        DrawRectangleLines(2,2,4*size,MAX_SIZE*size,BLACK);
        for(int i=0;i<MAX_SIZE;i++)
        {
            DrawText(BTN_NAME[i],2,(i*size)+2,size,BLACK);
        }

      
    }
    return ret;
}

