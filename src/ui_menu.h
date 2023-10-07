#ifndef UI_MENU_H
#define UI_MENU_H
#include "raylib.h"
struct UI_MENU
{
    int cursor;
    bool visible;
};
typedef struct UI_MENU UI_MENU;
UI_MENU UI_MENU_init();
void UI_MENU_update(UI_MENU* uimenu);
void UI_MENU_draw(UI_MENU* uimenu);
#endif