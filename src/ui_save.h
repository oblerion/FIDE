#ifndef UI_SAVE_H
#define UI_SAVE_H
#include "raylib.h"
struct UI_SAVE
{
    bool visible;
};
typedef struct UI_SAVE UI_SAVE;
UI_SAVE UI_SAVE_init();
void UI_SAVE_draw(UI_SAVE* uisave);
#endif