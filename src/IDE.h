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
struct IDE
{
	char file_name[40];
	struct CART cart;
	struct CURSOR cursor;
	char itext[2500][200];
	int font_size;
	unsigned int size;
	int max_size;
	int offsety;
};
struct IDE IDE_load(const char* file);
void IDE_update(struct IDE* side);
void IDE_draw(struct IDE* side);
#endif 
