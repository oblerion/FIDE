#pragma once
#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string2.h"
struct CART
{
	// info
	char title[40];
	char author[40];
	char desc[40];
	char site[40];
	char license[20];
	char version[10];
	char script[10];
	char input[10];
	// data
	char code[500000];
	char tile[255][65];
	char sprite[255][65];
	char map[240*(136+6)];
	char sfx[128*15];
	char tracks[128*64];
	char waves[21*15];
	char palette[(6+7)*15];
	char screen[100000];
	char flags[519*7];

};
struct CART CART_load(const char* file);
void CART_save(struct CART cart,char* file);
