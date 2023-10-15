#ifndef IDE_MENU_H
#define IDE_MENU_H
#include "raylib.h"
#include "ui.h"
struct IDE_MENU
{
    struct UI_FILEIO uifileio;
    bool visible;
};
struct IDE_MENU IDE_MENU();
void IDE_MENU_update(struct IDE_MENU* uimenu);
void IDE_MENU_draw(struct IDE_MENU* uimenu);
void IDE_MENU_free(struct IDE_MENU* uimenu);
#endif