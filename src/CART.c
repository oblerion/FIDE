#include "CART.h"
int _strfind(char* dstr,char* s,int posb)
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
const char* _TextExtractLine(char* s,char* sb,char ce)
{
	int ib = TextFindIndex(s,sb);
	if(ib>-1)
	{
		for(int i=ib;i<strlen(s);i++)
		{
			if(s[i]==ce)
			{
				return TextSubtext(s,ib+strlen(sb),i-(ib+strlen(sb)));
			}
		}
	}
	return "";
}
void _TextRemoveLine(char* s,char* sb,char ce)
{
	int ib = TextFindIndex(s,sb);
	if(ib>-1)
	{
		int ie=-1;
		for(int i=ib;i<strlen(s);i++)
		{
			if(s[i]==ce)
			{
				ie=i;
				break;
			}
		}
		if(ie>-1)
		{
			int rem_size = (ie+1)-ib;
			char lstr[strlen(s)-rem_size];
			int lpos=0;
			for(int i=0;i<strlen(s);i++)
			{
				if(i<ib || i>ie)
				{
					lstr[lpos] = s[i];
					lpos++;
				}
			}

			lstr[lpos]='\0';
			strcpy(s,lstr);
		}
	}
}
const char* _TextExtract(char* s,char* sb,char* se)
{
	int ib = TextFindIndex(s,sb);
	if(ib>-1)
	{
		int ie = _strfind(s,se,ib);
		if(ie>-1)
		{
			return TextSubtext(s,ib+strlen(sb),ie-(ib+strlen(sb)));
		}
	}
	return "";//lstr;
}
void _TextRemove(char* s,char* sb,char* se)
{
	int ib = TextFindIndex(s,sb);
	if(ib>-1)
	{
		int ie = _strfind(s,se,ib);
		if(ie>-1)
		{
			int size_rem = (ie+strlen(se))-ib;
			char strrem[strlen(s)-size_rem];
			int lpos = 0;
			for(int i=0;i<strlen(s);i++)
			{
				if(i<ib || i>ie+strlen(se))
				{
					strrem[lpos]=s[i];
					lpos++;
				}
			}
			strrem[lpos]='\0';
			strcpy(s,strrem);
		}
	}

}
struct CART CART_load(const char* file)
{
	char text[600000];
	FILE* fic = fopen(file,"r");
	if(fic!=NULL)
	{
		char lstr[200];
		//int pos=0;
		while(!feof(fic))
		{
			fgets(lstr,200,fic);
			if(!feof(fic))
			{
				strcat(text,TextFormat("%s",lstr));
			}
		}
		fclose(fic);
	}
	struct CART scart;

	strcpy(scart.title,_TextExtractLine(text,"-- title:",'\n'));
	strcpy(scart.author, _TextExtractLine(text,"-- author:",'\n'));
	strcpy(scart.desc, _TextExtractLine(text,"-- desc:",'\n'));
	strcpy(scart.site,_TextExtractLine(text,"-- site:",'\n'));
	strcpy(scart.license,_TextExtractLine(text,"-- license:",'\n'));
	strcpy(scart.script,_TextExtractLine(text,"-- script:",'\n'));
	strcpy(scart.version,_TextExtractLine(text,"-- version:",'\n'));

	strcpy(scart.tile,_TextExtract(text,"-- <TILES>\n","-- </TILES>"));
	strcpy(scart.sprite,_TextExtract(text,"-- <SPRITES>\n","-- </SPRITES>"));
	strcpy(scart.sfx,_TextExtract(text,"-- <SFX>\n","-- </SFX>"));
	strcpy(scart.tracks,_TextExtract(text,"-- <TRACKS>\n","-- </TRACKS>"));
	strcpy(scart.waves,_TextExtract(text,"-- <WAVES>\n","-- </WAVES>"));
	strcpy(scart.palette,_TextExtract(text,"-- <PALETTE>\n","-- </PALETTE>"));

	_TextRemoveLine(text,"-- title:",'\n');
	_TextRemoveLine(text,"-- author:",'\n');
	_TextRemoveLine(text,"-- desc:",'\n');
	_TextRemoveLine(text,"-- site:",'\n');
	_TextRemoveLine(text,"-- license:",'\n');
	_TextRemoveLine(text,"-- version:",'\n');
	_TextRemoveLine(text,"-- script:",'\n');

	_TextRemove(text,"\n-- <TILES>\n","\n-- </TILES>");
	_TextRemove(text,"\n-- <SPRITES>\n","\n-- </SPRITES>");
	_TextRemove(text,"\n-- <SFX>\n","\n-- </SFX>");
	_TextRemove(text,"\n-- <TRACKS>\n","\n-- </TRACKS>");
	_TextRemove(text,"\n-- <WAVES>\n","\n-- </WAVES>");
	_TextRemove(text,"\n-- <PALETTE>\n","\n-- </PALETTE>");
	strcpy(scart.code,text);
	printf("cart loading\n%s",text);
	return scart;
}
void CART_save(struct CART cart,char* file)
{
	char lstr[500000];
	strcpy(lstr,TextFormat("-- title:%s\n",cart.title));
	strcat(lstr,TextFormat("-- author:%s\n",cart.author));
	strcat(lstr,TextFormat("-- desc:%s\n",cart.desc));
	strcat(lstr,TextFormat("-- site:%s\n",cart.site));
	strcat(lstr,TextFormat("-- license:%s\n",cart.license));
	strcat(lstr,TextFormat("-- version:%s\n",cart.version));
	strcat(lstr,TextFormat("-- script:%s\n",cart.script));

	strcat(lstr,TextFormat("%s\n",cart.code));

	strcat(lstr,TextFormat("-- <TILES>\n%s-- </TILES>\n\n",cart.tile));
	strcat(lstr,TextFormat("-- <SPRITES>\n%s-- </SPRITES>\n\n",cart.sprite));
	strcat(lstr,TextFormat("-- <SFX>\n%s-- </SFX>\n\n",cart.sfx));
	strcat(lstr,TextFormat("-- <TRACKS>\n%s-- </TRACKS>\n\n",cart.tracks));

	strcat(lstr,TextFormat("-- <WAVES>\n%s-- </WAVES>\n",cart.waves));
	strcat(lstr,TextFormat("-- <PALETTE>\n%s-- </PALETTE>\n",cart.palette));

	FILE* fic = fopen(file,"w");
	if(fic!=NULL)
	{
		fprintf(fic,"%s",lstr);
		fclose(fic);
	}
}
