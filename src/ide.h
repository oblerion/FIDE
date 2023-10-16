#ifndef IDE_H
#define IDE_H
#include "raylib.h"
#include "kbd_layout.h"
#include "ide_menu.h"
#include "ide_parameter.h"
#include "ui.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define MAX_LINE 2500
struct CURSOR 
{
	int x;
	int y;
	float timer;
	Color color;
};

struct IDE
{
	
	struct CURSOR cursor;
	struct IDE_MENU uimenu;
    struct UI_FILEIO uifileio;
	struct IDE_PARAMETER idepara;
	KBD_Layout layout;
	
	char file_name[124];
	char itext[MAX_LINE][200];
	int font_size;
	unsigned int size;
	int max_size;
	int offsety;
	int offset_borderx;
	float timer;
};
void IDE_load(struct IDE* side,const char* file);
void IDE_update(struct IDE* side);
void IDE_draw(struct IDE* side);
void IDE_free(struct IDE* side);
#endif 
