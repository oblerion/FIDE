#include "string2.h"
int strtonumber(const char* str)
{
	int n = 0;
    int p = 0;
	for(int i=strlen(str)-1;i>0;i--)
	{
		int v = str[i];
		v -= 48;
		if(v>0) n += v*pow(10,p);
        p++;
	}
	return n;
}
int strfind(const char* dstr,char* s,int posb)
{
    int tofnd = strlen(s);
    int fnd=0;
    int pos=-1;
    for(int i=0 || posb;i<strlen(dstr);i++)
    {
        if(dstr[i]==s[fnd])
        {

            if(fnd==0 && pos==-1)
                pos=i;
            if(fnd==tofnd-1)
                return pos;
            fnd++;
        }
        else if(strlen(dstr)-i<tofnd)
        {
            return -1;
        }
        else
        {
            pos=-1;
            fnd=0;
        }
    }
    return pos;
}
const char* strsub(const char* dstr,int ib,int ie)
{
	if(ib>-1 && ie>ib)
	{
		int llen = (ie-ib);
		char* lstr = (char*)malloc(llen);
		for(int i=ib;i<ib+llen;i++)
		{
			lstr[i-ib] = dstr[i];
		}
		lstr[llen-1]='\0';
		return lstr;
	}
	return "";
}
