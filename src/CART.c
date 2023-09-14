#include "CART.h"

const char* _TextExtractLine(char* s,char* sb,char ce)
{
	int ib = strfind(s,sb,0);
	if(ib>-1)
	{
		for(int i=ib;i<strlen(s)-ib;i++)
		{
			if(s[i]==ce)
			{
				return strsub(s,ib+strlen(sb),i+1);
			}
		}
	}
	return "";
}
void _TextRemoveLine(char* s,char* sb,char ce)
{
	int ib = strfind(s,sb,0);
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
	int ib = strfind(s,sb,0);
	if(ib>-1)
	{
		int ie = strfind(s,se,ib);
		if(ie>-1)
		{
			const char* cstr = strsub(s,ib+strlen(sb),ie);
			printf("extract %s\n",cstr);
			return cstr;
		}
	}
	return "";//lstr;
}
void _TextRemove(char* s,char* sb,char* se)
{
	int ib = strfind(s,sb,0);
	if(ib>-1)
	{
		int ie = strfind(s,se,ib);
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
void _LoadTile(struct CART* cart,char* text)
{

	const char* cstr = _TextExtract(text,"-- <TILES>\n","-- </TILES>");
	int past_pos = 0;
	for(int i=0;i<=strlen(cstr);i++)
	{
		if(cstr[i]=='\n' || i==strlen(cstr))
		{
			char line[71];
			strcpy(line,strsub(cstr,past_pos,i+1));
			int id = strtonumber(strsub(line,3,7));
			char data[65];
			strcpy(data,strsub(line,7,7+65));
			strcpy(cart->tile[id],data);
			past_pos = i+1;
		}
	}
}
void _LoadSprite(struct CART* cart,char* text)
{

	const char* cstr = _TextExtract(text,"-- <SPRITES>\n","-- </SPRITES>");
	int past_pos = 0;
	for(int i=0;i<=strlen(cstr);i++)
	{
		if(cstr[i]=='\n' || i==strlen(cstr))
		{
			char line[71];
			strcpy(line,strsub(cstr,past_pos,i+1));
			int id = strtonumber(strsub(line,3,7));
			char data[65];
			strcpy(data,strsub(line,7,7+65));
			strcpy(cart->sprite[id],data);
			past_pos = i+1;
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
		while(1)
		{
			fgets(lstr,200,fic);
			if(!feof(fic))
			{
				const char* cstr = TextFormat("%s",lstr);
				strcat(text,cstr);
			}
			else
				break;
		}
		fclose(fic);
	}
	struct CART scart;

	// strcpy(scart.title,_TextExtractLine(text,"-- title:",'\n'));
	// strcpy(scart.author, _TextExtractLine(text,"-- author:",'\n'));
	// strcpy(scart.desc, _TextExtractLine(text,"-- desc:",'\n'));
	// strcpy(scart.site,_TextExtractLine(text,"-- site:",'\n'));
	// strcpy(scart.license,_TextExtractLine(text,"-- license:",'\n'));
	// strcpy(scart.script,_TextExtractLine(text,"-- script:",'\n'));
	// strcpy(scart.version,_TextExtractLine(text,"-- version:",'\n'));
	// strcpy(scart.input,_TextExtractLine(text,"-- input:",'\n'));

	// strcpy(scart.tile,_TextExtract(text,"-- <TILES>\n","-- </TILES>"));
	_LoadTile(&scart,text);
	// strcpy(scart.sprite,_TextExtract(text,"-- <SPRITES>\n","-- </SPRITES>"));
	// strcpy(scart.sfx,_TextExtract(text,"-- <SFX>\n","-- </SFX>"));
	// strcpy(scart.tracks,_TextExtract(text,"-- <TRACKS>\n","-- </TRACKS>"));
	// strcpy(scart.waves,_TextExtract(text,"-- <WAVES>\n","-- </WAVES>"));
	// strcpy(scart.palette,_TextExtract(text,"-- <PALETTE>\n","-- </PALETTE>"));
	// strcpy(scart.map,_TextExtract(text,"-- <MAP>\n","-- </MAP>"));
	// puts("begin : extract screen");
	// strcpy(scart.screen,_TextExtract(text,"\n-- <SCREEN>\n","\n-- </SCREEN>"));
	// strcpy(scart.flags,_TextExtract(text,"-- <FLAGS>\n","-- </FLAGS>"));

	_TextRemoveLine(text,"-- title:",'\n');
	_TextRemoveLine(text,"-- author:",'\n');
	_TextRemoveLine(text,"-- desc:",'\n');
	_TextRemoveLine(text,"-- site:",'\n');
	_TextRemoveLine(text,"-- license:",'\n');
	_TextRemoveLine(text,"-- version:",'\n');
	_TextRemoveLine(text,"-- script:",'\n');
	_TextRemoveLine(text,"-- input:",'\n');

	_TextRemove(text,"-- <TILES>\n","-- </TILES>");
	_TextRemove(text,"-- <SPRITES>\n","-- </SPRITES>");
	_TextRemove(text,"-- <SFX>\n","-- </SFX>");
	_TextRemove(text,"-- <TRACKS>\n","-- </TRACKS>");
	_TextRemove(text,"-- <WAVES>\n","-- </WAVES>");
	_TextRemove(text,"-- <PALETTE>\n","-- </PALETTE>");

	_TextRemove(text,"-- <MAP>\n","-- </MAP>");
	_TextRemove(text,"-- <SCREEN>\n","-- </SCREEN>");
	_TextRemove(text,"-- <FLAGS>\n","-- </FLAGS>");
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

	strcat(lstr,TextFormat("-- <TILES>\n%s\n-- </TILES>\n\n",cart.tile));
	strcat(lstr,TextFormat("-- <SPRITES>\n%s\n-- </SPRITES>\n\n",cart.sprite));
	strcat(lstr,TextFormat("-- <SFX>\n%s\n-- </SFX>\n\n",cart.sfx));
	strcat(lstr,TextFormat("-- <TRACKS>\n%s\n-- </TRACKS>\n\n",cart.tracks));

	strcat(lstr,TextFormat("-- <WAVES>\n%s\n-- </WAVES>\n\n",cart.waves));
	strcat(lstr,TextFormat("-- <PALETTE>\n%s\n-- </PALETTE>\n\n",cart.palette));

	FILE* fic = fopen(file,"w");
	if(fic!=NULL)
	{
		fprintf(fic,"%s",lstr);
		fclose(fic);
	}
}
