#pragma once 
#include "raylib.h"
#include "stdlib.h"

struct CURSOR 
{
	int x;
	int y;
	float timer;
	Color color;
	int pos;
};

struct FIDE
{
    int font_size;
    struct CURSOR cursor;
    char* text;
    int max_size;
};

struct FIDE FIDE(int font_size);
void FIDE_Load(struct FIDE* fide,const char* file);
void FIDE_Draw(struct FIDE* fide);
void FIDE_Free(struct FIDE* fide);

