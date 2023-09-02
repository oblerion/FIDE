#ifndef CART_H
#define CART_H
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
	// data
	char code[500000];
	char tile[71*255];
	char sprite[71*255];
	char map[2000];
	char sfx[128*15];
	char tracks[128*64];
	char waves[21*15];
	char palette[(6+7)*15];
};
struct CART CART_load(const char* file);
void CART_save(struct CART cart,char* file);
#endif
