#include "math.h"

int MATH_collide(int x,int y,int w,int h,int x2,int y2,int w2,int h2)
{
	if(x+w>x2 && x<x2+w2 && y+h>y2 && y2+h2>y) return 1;
	return 0;
}
