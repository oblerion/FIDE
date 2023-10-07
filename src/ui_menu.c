#include "ui_menu.h"
#define MAX_SIZE 3
const char BTN_NAME[MAX_SIZE][10] = 
{
    "[o]pen",
    "[s]ave",
    "[c]lose"
};

UI_MENU UI_MENU_init()
{
    struct UI_MENU uimenu;
    uimenu.cursor=0;
    uimenu.visible=0;
    return uimenu;
}

void UI_MENU_update(UI_MENU* uimenu)
{
    if(uimenu->visible==1)
    {
        if(IsKeyPressed(KEY_O)) {}
        else if(IsKeyPressed(KEY_S)){}
        else if(IsKeyPressed(KEY_C)){}
    }
}

void UI_MENU_draw(UI_MENU* uimenu)
{
    if(uimenu->visible==1)
    {
        const int size = 24;
        DrawRectangle(2,2,4*size,MAX_SIZE*size,BLUE);
        DrawRectangleLines(2,2,4*size,MAX_SIZE*size,BLACK);
        for(int i=0;i<MAX_SIZE;i++)
        {
            DrawText(BTN_NAME[i],2,(i*size)+2,size,BLACK);
        }
    }
}
