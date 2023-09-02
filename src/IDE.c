#include "IDE.h"

void _ITEXT_init(struct IDE* ide)
{
	int ic=0;
	int il=0;

	for(int pos=0;pos<strlen(ide->cart.code);pos++)
	{
		char lchar = ide->cart.code[pos];
		if(lchar!='\n')
		{
			ide->itext[il][ic] = lchar;
			ic++;
		}
		else
		{
			ic=0;
			if(il+1<200) il++;
			else break;
		}
	}
}
void _ITEXT_toCart(struct IDE* ide)
{
	strcpy(ide->cart.code,"");
	for(int y=0;y<2500;y++)
	{
		if(strlen(ide->itext[y])>0)
			strcat(ide->cart.code,TextFormat("%s\n",ide->itext[y]));
	}
}
void _CURSOR_draw(struct IDE* ide)
{

	if(ide->cursor.timer>0)
	{
		int y = 20+ide->cursor.y*ide->font_size;
		int x = 20+MeasureText(TextSubtext(ide->itext[ide->cursor.y],0,ide->cursor.x),ide->font_size);
		// const char* schar = TextFormat("%c",ide.itext[ide.cursor.y][ide.cursor.x]);
		DrawRectangleLines(x,y,3,ide->font_size,ide->cursor.color);

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
	if(side->cursor.y+1<2500) side->cursor.y++;
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
struct IDE IDE_load(const char* file)
{
	struct IDE side;
	side.offsety=0;
	side.font_size=25;
	side.max_size = 500000;
	strcpy(side.file_name,file);
	printf("\nsize %d\n",TextLength(LoadFileText(file)));
	side.cart = CART_load(file);
	printf("get code\n %s",side.cart.code);
	_ITEXT_init(&side);
	side.size = TextLength(side.cart.code);
	side.cursor = CURSOR_init();
	return side;
}
void IDE_update(struct IDE* side)
{
	int key = GetKeyPressed();

	switch(key)
	{
		case KEY_LEFT:
			if(side->cursor.x>0) side->cursor.x--;
		break;
		case KEY_RIGHT:
			if(side->cursor.x+1 < 199) side->cursor.x++;
		break;
		case KEY_DOWN:
			_IDE_gotoNextLine(side);
		break;
		case KEY_UP:
			_IDE_gotoBeforeLine(side);
		break;
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
			if(side->cursor.x==0)
			{
				for(int i=2498;i>=side->cursor.y;i--)
				{
						strcpy(side->itext[i+1],side->itext[i]);
						strcpy(side->itext[i],"");
				}
				side->cursor.y++;
			}
			else if(side->cursor.x==strlen(side->itext[side->cursor.y]))
			{
				if(side->cursor.y<2500)
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
			_ITEXT_toCart(side);
			CART_save(side->cart,"t.lua");
		break;
		default:

			if(key>=KEY_A && key<=KEY_Z)
			{
				const char* lc = TextToLower(TextFormat("%c",key));
				_IDE_addChar(side,*lc);
			}
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
	for(int y=0;y<2500;y++)
	{
		DrawText(side->itext[y],20,20+(y*side->font_size),side->font_size,BLACK);
	}
	_CURSOR_draw(side);
}

