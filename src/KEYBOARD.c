#include "KEYBOARD.h"

int _ToAzerty(int c)
{
    switch(c)
    {
        case KEY_A : return KEY_Q;
        case KEY_Z : return KEY_W;
        case KEY_Q : return KEY_A;
        case KEY_W : return KEY_Z;
        case KEY_SEMICOLON : return KEY_M;
        case KEY_M : return KEY_COMMA;
    }
    return c;
}
int _ToAzerty_bel_var(int c)
{
    int key;
    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    bool alt = IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT);
    printf("char %c \n",c);
    if( c >= KEY_A && c <= KEY_Z)
    {
        if(shift)
            key = c;
        else 
            key = c + 32;
    }

    switch(c)
    {
        case KEY_ONE :
            if(shift)
                key = KEY_ONE;
            else if(alt)
                key = 124;
            else 
                key = 38;
        break;
        case KEY_TWO : 
            if(shift) 
                key = KEY_TWO;
            else if(alt) 
                key = 64;
            else
                key = 130;
        break;
        case KEY_THREE : 
            if(shift) 
                key = KEY_THREE;
            else if( alt) 
                key = 35;
            else 
                key = 34;
        break;
        case KEY_FOUR : 
            if(shift)
                key = KEY_FOUR;
            else
                key = 39;
        break;
        case KEY_FIVE : 
            if(shift)
                key = KEY_FIVE;
            else 
                key = 40;
        break;
        case KEY_SIX : 
            if(shift)
                key = KEY_SIX;
            else
                key = 245;
        break;
        case KEY_SEVEN : 
            if(shift)
                key = KEY_SEVEN;
            else
                key = 138;
        break;
        case KEY_EIGHT :
            if(shift)
                key = KEY_EIGHT;
            else 
                key = 33;
        break;
        case KEY_NINE :
            if(shift)
                key = KEY_NINE;
            else if(alt)
                key = 123;
            else 
                key = 128;
        break;
        case KEY_ZERO : 
            if(shift)
                key = KEY_ZERO;
            else if(alt)
                key = 125;
            else 
                key = 133;
        break;

    }
    return key;
}
int Kbd_GetKeyPressed(enum KbdLayout layout)
{
	int c = GetKeyPressed();
    if(layout == KBD_FR_BEL_VAR)
    {
        c = _ToAzerty(c);
        c = _ToAzerty_bel_var(c);
    }
    else if(layout == KBD_EN)
    {

    }
	return c;
}

int Kbd_IsKeyDown(enum KbdLayout layout,int key)
{

    if(layout == KBD_FR_BEL_VAR) 
    {
        int c = _ToAzerty(key);
        c = _ToAzerty_bel_var(c);
        return IsKeyDown(c);
    }
    return IsKeyDown(key);
}