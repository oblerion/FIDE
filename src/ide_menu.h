#ifndef IDE_MENU_H
#define IDE_MENU_H
#include "raylib.h"
struct IDE_MENU
{
    bool visible;
};
enum IDE_MENU_ID
{
    MENU_default=0,
    MENU_open=1,
    MENU_save=2,
    MENU_parameter=3
};
typedef enum IDE_MENU_ID IDE_MENU_ID;
struct IDE_MENU IDE_MENU();
IDE_MENU_ID IDE_MENU_draw(struct IDE_MENU* uimenu);
#endif