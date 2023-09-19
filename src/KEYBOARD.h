#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "raylib.h"
enum KbdLayout
{
    KBD_EN = 0,
    KBD_FR_BEL_VAR = 1
};

int Kbd_GetKeyPressed(enum KbdLayout layout);
int Kbd_IsKeyDown(enum KbdLayout layout,int key);
#endif