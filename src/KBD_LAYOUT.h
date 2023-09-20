#ifndef KBD_LAYOUT_H
#define KBD_LAYOUT_H
#include "raylib.h"

typedef enum 
{
    EN=-1,
    FR_BEL_VAR=0
}KBD_Layout;

int Kbd_GetKeyPressed(KBD_Layout layout);
#endif