#include "ide_menu.h"
#define MAX_SIZE 3
const char BTN_NAME[MAX_SIZE][10] = 
{
    "[o]pen",
    "[s]ave",
    "[c]lose"
};

struct IDE_MENU IDE_MENU()
{
    struct IDE_MENU uimenu;
    uimenu.uifileio = UI_FILEIO(30,30,BLACK);
    uimenu.uifileio.visible=false;
    uimenu.visible=0;
    return uimenu;
}

void IDE_MENU_update(struct IDE_MENU* uimenu)
{
    if(uimenu->visible==1)
    {
        if(IsKeyDown(KEY_LEFT_CONTROL) || 
            IsKeyDown(KEY_RIGHT_CONTROL))
        {
            if(IsKeyPressed(KEY_O) && uimenu->uifileio.visible==false) 
            {
                uimenu->uifileio.visible=true;
            }
            else if(IsKeyPressed(KEY_S))
            {

            }
            else if(IsKeyPressed(KEY_C))
            {

            }
        }
    }
}

void IDE_MENU_draw(struct IDE_MENU* uimenu)
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
    if(UI_FILEIO_draw(&uimenu->uifileio,1)==1)
    {
        uimenu->uifileio.visible=false;
    }
}

void IDE_MENU_free(struct IDE_MENU *uimenu)
{
    UI_FILEIO_free(&uimenu->uifileio);
}
