#include "ui.h"

struct UI_BUTTON UI_BUTTON(int x, int y, char *name, int size_font, Color color)
{
    struct UI_BUTTON uibutton;
    uibutton.x = x;
    uibutton.y = y;
    strcpy(uibutton.name,name);
    uibutton.size_font = size_font;
    uibutton.color = color;
    uibutton.visible=true;

    uibutton.width = MeasureText(name,uibutton.size_font)+8;
    uibutton.height = size_font+8;
    return uibutton;
}


bool UI_BUTTON_draw(struct UI_BUTTON *uibutton)
{
    bool lbool = false;
    if(uibutton->visible)
    {
        Color lcol = uibutton->color;
        if(MATH_collide(GetMouseX(),GetMouseY(),10,10,
            uibutton->x-4,uibutton->y-4,uibutton->width,uibutton->height)==1)
        {
            lcol.a = 50;
            if(IsMouseButtonPressed(0)) lbool = true;
        }
        DrawRectangleLines(uibutton->x-4,uibutton->y-4,uibutton->width,uibutton->height,lcol);
        DrawText(uibutton->name,uibutton->x,uibutton->y,uibutton->size_font,lcol);
    }
    return lbool;
}

struct UI_TEXT_FIELD UI_TEXT_FIELD(int x, int y, char *text, int size_font, Color color)
{
    struct UI_TEXT_FIELD uitextf;
    uitextf.x = x;
    uitextf.y = y;
    strcpy(uitextf.text,text);
    uitextf.size_font=size_font;
    uitextf.color=color;

    uitextf.width = MeasureText(text,size_font)+8;
    uitextf.height = size_font+8;
    return uitextf;
}

void UI_TEXT_FIELD_draw(struct UI_TEXT_FIELD* uitextfield)
{
    if(uitextfield->visible)
    {
        DrawText(uitextfield->text,uitextfield->x,uitextfield->y,uitextfield->size_font,uitextfield->color);
    }
}