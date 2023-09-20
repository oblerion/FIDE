#ifndef IDE_H
#define IDE_H
#include "raylib.h"
#include "cursor.h"
#include "kbd_layout.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define MAX_LINE 2500

struct IDE
{
	char file_name[40];
	struct CURSOR cursor;
	char itext[MAX_LINE][200];
	char kbd_layout[20];
	int font_size;
	unsigned int size;
	int max_size;
	int offsety;
	float timer;
};
void IDE_load(struct IDE* side,const char* file);
void IDE_update(struct IDE* side);
void IDE_draw(struct IDE* side);
#endif 
