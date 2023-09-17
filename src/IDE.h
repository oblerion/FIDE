#ifndef IDE_H
#define IDE_H
#include "raylib.h"
#include "CURSOR.h"
#include "CART.h"
#include "MATH.h"
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
