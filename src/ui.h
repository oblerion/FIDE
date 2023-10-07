#ifndef UI_H
#define UI_H
#include "raylib.h"
#include "math.h"
#include <string.h>
struct UI_BUTTON
{
    int x;
    int y;
    int width;
    int height;
    int size_font;
    char name[30];
    Color color;

    bool visible;
};
struct UI_BUTTON UI_BUTTON(int x,int y,char* name,int size_font,Color color);
bool UI_BUTTON_draw(struct UI_BUTTON* uibutton);

struct UI_TEXT_FIELD
{
    int x;
    int y;
    int width;
    int height;
    int size_font;
    char* text;
    Color color;

    bool visible;
};
struct UI_TEXT_FIELD UI_TEXT_FIELD(int x,int y,char* text,int size_font,Color color);
void UI_TEXT_FIELD_draw(struct UI_TEXT_FIELD* uitextfield);
#endif