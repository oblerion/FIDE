#include "ide.h"


void _ITEXT_init(struct IDE* ide,const char* code)
{
	int ic=0;
	int il=0;
	for(int pos=0;pos<strlen(code)-1;pos++)
	{
		char lchar = code[pos];
		if(lchar!='\n')
		{
			ide->itext[il][ic] = lchar;
			ic++;
		}
		else
		{
			ide->itext[il][ic] = '\0';
			ic=0;
			if(il+1<2499) il++;
			else break;
		}
	}
	for(int y=il;y<MAX_LINE;y++)
	{
		ide->itext[y][0] = '\0';
	}
}
// void _ITEXT_toCart(struct IDE* ide)
// {
// 	strcpy(ide->cart.code,"");
// 	int ret_count = 0;
// 	for(int y=0;y<2499;y++)
// 	{

// 		strcat(ide->cart.code,TextFormat("%s\n",ide->itext[y]));
// 		if(strlen(ide->itext[y])<2) ret_count++;
// 		else ret_count=0;

// 		if(ret_count==3) break;

// 	}
// }
void _CURSOR_draw(struct IDE* ide)
{

	if(ide->cursor.timer>0)
	{
		int y = 20+ide->cursor.y*ide->font_size;
		int x = 20+MeasureText(TextSubtext(ide->itext[ide->cursor.y],0,ide->cursor.x),ide->font_size);
		// const char* schar = TextFormat("%c",ide.itext[ide.cursor.y][ide.cursor.x]);
		DrawRectangleLines(x,y-(ide->offsety*ide->font_size),3,ide->font_size,ide->cursor.color);

		ide->cursor.timer -= GetFrameTime();
	}
	else if(ide->cursor.timer<0)
	{
		ide->cursor.timer -= GetFrameTime();
		if(ide->cursor.timer<-0.2)
			ide->cursor.timer = 0.3;
	}
}

void _IDE_gotoNextLine(struct IDE* side)
{
	if(side->cursor.y+1<MAX_LINE) side->cursor.y++;
}
void _IDE_gotoBeforeLine(struct IDE* side)
{
	if(side->cursor.y-1>-1) side->cursor.y--;
}
int _IDE_ifCollideMouse(struct IDE side)
{
	// int ix = 0;
	// int iy = 0;
 //
	// for(int i=0;i<side.size;i++)
	// {
	// 	char ich = side.cart.code[i]; //side.list_char[i];
	// 	const char* schar = TextFormat("%c",ich);
	// 	//DrawText(schar,20+ix,20+iy,side.font_size,BLACK);
	// 	if(MATH_collide(ix+20,iy+20,MeasureText(schar,side.font_size),side.font_size,GetMouseX(),GetMouseY(),10,10)==1)
	// 	{
	// 		return i;
	// 	}
	// 	if(*schar=='\n')
	// 	{
	// 		iy += side.font_size;
	// 		ix = 0;
	// 	}
	// 	else
	// 	{
	// 		ix += MeasureText(schar,side.font_size)+2;
	// 	}
	// }
	return -1;
}
void _IDE_addChar(struct IDE* ide,char c)
{
	struct CURSOR cursor = ide->cursor;
	int lenline = strlen(ide->itext[cursor.y]);
	if(lenline+1<200)
	{
		if(cursor.x>0)
		{
			char str1[200];
			strcpy(str1,TextSubtext(ide->itext[cursor.y],0,cursor.x));
			char str2[200];
			strcpy(str2,TextSubtext(ide->itext[cursor.y],cursor.x,strlen(ide->itext[cursor.y])-cursor.x));
			strcpy(ide->itext[cursor.y],TextFormat("%s%c%s",str1,c,str2));
			ide->cursor.x++;
		}
		else if(cursor.x==0)
		{
			strcpy(ide->itext[cursor.y],TextFormat("%c%s",c,ide->itext[cursor.y]));
			ide->cursor.x++;
		}
	}
}
void _IDE_remChar(struct IDE* ide)
{
	int pos = ide->cursor.x;
	int lenline = strlen(ide->itext[ide->cursor.y]);
	if(pos>0)
    {
        if(lenline>1)
        {
			char lc[200];
			int lpos=0;
			for(int i=0;i<lenline;i++)
			{
				if(i!=pos-1){
					lc[lpos]=ide->itext[ide->cursor.y][i];
					lpos++;
				}
				if(lenline-1==i)
					lc[i]='\0';
			}
			strcpy(ide->itext[ide->cursor.y],lc);
			ide->cursor.x--;
        }
        else if(lenline==1)
		{
			strcpy(ide->itext[ide->cursor.y],"");
			ide->itext[ide->cursor.y][0]='\0';
		}
    }
    else if(pos==0)
	{
		if(ide->cursor.y>0)
		{
			ide->cursor.y--;
			ide->cursor.x = strlen(ide->itext[ide->cursor.y]);
		}
	}
}
void IDE_load(struct IDE* side,const char* file)
{
	side->offsety=0;
	side->font_size=25;
	side->max_size = 500000;
	strcpy(side->file_name,file);
	//side->cart = CART_load(file);
	//printf("get code\n %s",side->cart.code);
	//_ITEXT_init(side);
	_ITEXT_init(side,LoadFileText(file));
	side->cursor = CURSOR_init();
}
void IDE_update(struct IDE* side)
{
	if(side->timer<=0)
	{
		if(IsKeyDown(KEY_LEFT))
		{
			if(side->cursor.x>0) side->cursor.x--;
			side->timer = 0.06f;
		}
		else if(IsKeyDown(KEY_RIGHT))
		{
			if(side->cursor.x < strlen(side->itext[side->cursor.y]))
			{
				side->cursor.x++;				
			}
			side->timer = 0.06f;
		}
		else if(IsKeyDown(KEY_DOWN))
		{
			_IDE_gotoNextLine(side);
			if(side->cursor.y>side->offsety+34) 
			{
				side->offsety++;
			}
			side->timer = 0.05f;
		}
		else if(IsKeyDown(KEY_UP))
		{
			_IDE_gotoBeforeLine(side);
			if(side->cursor.y==side->offsety && side->offsety>0) 
			{
				side->offsety--;
			}
			side->timer = 0.05f;
		}
		else if(GetMouseWheelMove()<0)
		{
			_IDE_gotoNextLine(side);
			_IDE_gotoNextLine(side);
			if(side->cursor.y>side->offsety+34) 
			{
				side->offsety+=2;
			}
			side->timer = 0.03f;
		}
		else if(GetMouseWheelMove()>0)
		{
			_IDE_gotoBeforeLine(side);
			_IDE_gotoBeforeLine(side);
			if(side->cursor.y==side->offsety && side->offsety>1) 
			{
				side->offsety-=2;
			}
			side->timer = 0.03f;
		}
	}
	else
		side->timer -= GetFrameTime();

	//int key = _Azerty_GetKeyPressed();
	int key = Kbd_GetKeyPressed(FR);
	//int key=0;
	switch(key)
	{
		case KEY_BACKSPACE:
			_IDE_remChar(side);
		break;
		case KEY_SPACE:
			_IDE_addChar(side,' ');
		break;
		case KEY_TAB:
			_IDE_addChar(side,'\t');
		break;
		case KEY_ENTER:
			// if(side->cursor.x==0)
			// {
			// 	for(int i=MAX_LINE-1;i>=side->cursor.y+1;i--)
			// 	{
			// 			strcpy(side->itext[i+1],side->itext[i]);
			// 			strcpy(side->itext[i],"");
			// 	}
			// 	side->cursor.y++;
			// }
			// else 
			if(side->cursor.x==strlen(side->itext[side->cursor.y]))
			{
				if(side->cursor.y<MAX_LINE)
				{
					side->cursor.x=0;
					side->cursor.y++;
				}
			}
		break;
		case KEY_F5:
			system(TextFormat("tic80 --skip %s",side->file_name));
		break;
		case KEY_F1:
			//_ITEXT_toCart(side);
			//CART_save(side->cart,"t.lua");
		break;
		default:
			//const char* lc = TextFormat("%c",key);
			if( key != KEY_LEFT_SHIFT && 
				key != KEY_RIGHT_SHIFT && 
				key != KEY_LEFT_ALT &&
				key != KEY_RIGHT_ALT)
			_IDE_addChar(side,*TextFormat("%c",key));
			// if((key>=KEY_A && key<=KEY_Z))
			// {
			// 	if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
			// 	{
			// 		const char* lc = TextFormat("%c",key);
			// 		_IDE_addChar(side,*lc);
			// 	}
			// 	else
			// 	{
			// 		const char* lc = TextToLower(TextFormat("%c",key));
			// 		_IDE_addChar(side,*lc);
			// 	}
			// }
			// else if(key>=KEY_ZERO && key<=KEY_NINE)
			// {
			// 	if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
			// 	{
			// 		const char* lc = TextFormat("%c",key);
			// 		_IDE_addChar(side,*lc);
			// 	}	
			// }
		break;
	}
	
	if(IsMouseButtonPressed(0))
	{
		// int id = _IDE_ifCollideMouse(*side);
		// if(id !=-1)
		// {
		// 	side->cursor.pos = id;
		// }
	}
	
}

void IDE_draw(struct IDE* side)
{
// 2499
	for(int y=side->offsety;y<side->offsety+35;y++)
	{
		if(side->itext[y][0]!='\0')
		{
			DrawText(side->itext[y],20,20+(y*side->font_size)-(side->offsety*side->font_size),side->font_size,BLACK);
		}
	}
	_CURSOR_draw(side);
}

