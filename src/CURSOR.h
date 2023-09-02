#ifndef CURSOR_H
#define CURSOR_H
#include "raylib.h"
struct CURSOR 
{
	int x;
	int y;
	float timer;
	Color color;
};
struct CURSOR CURSOR_init();
//void CURSOR_draw(struct CURSOR cur);
#endif
