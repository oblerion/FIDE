#ifndef STRING2_H
#define STRING2_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int strtonumber(const char* str);
int strfind(const char* dstr,char* s,int posb);
const char* strsub(const char* dstr,int ib,int ie);
#endif