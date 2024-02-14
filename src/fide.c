#include "fide.h"
#include "string2.h"


struct CURSOR CURSOR()
{
	struct CURSOR cur ={
		0,0,0.5f,WHITE,0
	};
	return cur;
}

bool CURSOR_Timer(struct CURSOR* cursor)
{
    bool rbool = false;
    if(cursor->timer<-0.2)
		cursor->timer = 0.3;
	else
    {
        cursor->timer -= GetFrameTime();
        rbool = true;
    }
    return rbool;
}

void CURSOR_draw(struct CURSOR* cursor,int px,int py,int ph)
{
    if(CURSOR_Timer(cursor))
	{
		cursor->timer -= GetFrameTime();
		int x = px+cursor->x;
		int y = py+cursor->y;
        DrawRectangleLines(x,y,3,ph,cursor->color);
	}
}

struct FIDE FIDE(int pfont_size)
{
    struct FIDE fide = {
        pfont_size,
        CURSOR(),
        NULL,
        0
    };
    return fide;
}

void FIDE_Load(struct FIDE *fide, const char *file)
{
    if(FileExists(file))
    {
        char* text = LoadFileText(file);
        fide->text = (char*)malloc(strlen(file)+500);
        fide->max_size=strlen(file)+500;
        strcpy(fide->text,text);
        UnloadFileText(text);
    }
}

void _FIDE_MoveCursor(struct FIDE *fide)
{
    if(IsKeyPressed(KEY_RIGHT))
    {
        if(fide->cursor.pos+1<fide->max_size &&
            fide->cursor.pos+1 < strlen(fide->text))
        {
            // if(fide->text[ fide->cursor.pos+1] == '\n') 
            //     fide->cursor.pos+=2;
            // else
                fide->cursor.pos++;
        }
    }
    if(IsKeyPressed(KEY_LEFT))
    {
        if(fide->cursor.pos>0)
        {
            // if(fide->text[ fide->cursor.pos-1] == '\n') 
            //     fide->cursor.pos-=2;
            // else 
                fide->cursor.pos--;
        }
    }
}

void _FIDE_DrawText(struct FIDE *fide)
{
    const int offx = 20;
    const int offy = 10;
    const int size = strlen(fide->text);

    int tmp_pos = 0;
    int tmp_y = 0;
    for(int i=0;i<size;i++)
    {
        if(fide->text[i]=='\n' || i+1==size)
        {
            const char* sstr = TextSubtext(fide->text,tmp_pos,i-tmp_pos); 
            DrawText(sstr,offx,offy+tmp_y,fide->font_size,BLACK);
            tmp_y += fide->font_size;               
            tmp_pos=i+1;
        }

        if(i==fide->cursor.pos)
        {
            const char* before_cur = TextSubtext(fide->text,tmp_pos,fide->cursor.pos-tmp_pos);      
            fide->cursor.x = MeasureText(before_cur,fide->font_size); 
            fide->cursor.y = tmp_y;        
        }
    }
    CURSOR_draw(&fide->cursor,offx,offy,fide->font_size);
}

char _TextMaj(char c)
{
    char lc = c;
    if(c>=KEY_A+32 && c<=KEY_Z+32)
    {
        lc -= 32;
    }
    return lc;
}

void _FIDE_AddChar(struct FIDE *fide,char k)
{
    if(fide->max_size>strlen(fide->text)+1)
    {
        strcat(fide->text," ");
        for(int i=strlen(fide->text)-1;i>fide->cursor.pos;i--)
        {
            fide->text[i] = fide->text[i-1];
        }
        fide->text[fide->cursor.pos]=k;
        fide->cursor.pos++;
    }
}

void _FIDE_DelChar(struct FIDE *fide)
{
    const int lp = fide->cursor.pos-1;
    if(lp>=0)
    {
        for(int i=lp;i<strlen(fide->text);i++)
        {
            fide->text[i] = fide->text[i+1];
        } 
        fide->cursor.pos=lp;
    }
}


void _FIDE_Input(struct FIDE *fide)
{
    const int ck = GetCharPressed();
    if((IsKeyDown(KEY_RIGHT_SHIFT) || 
        IsKeyDown(KEY_LEFT_SHIFT))
        && (ck>=KEY_A && ck<=KEY_Z))
            _FIDE_AddChar(fide,ck);
    else if((ck>=KEY_A+32 && ck<=KEY_Z+32))
            _FIDE_AddChar(fide,ck);

    if(IsKeyPressed(KEY_ENTER))
    {
        _FIDE_AddChar(fide,'\n');
    }
    else if(IsKeyPressed(KEY_SPACE))
    {
        _FIDE_AddChar(fide,' ');
    }
    else if(IsKeyPressed(KEY_BACKSPACE))
    {
        _FIDE_DelChar(fide);
    }
} 

void FIDE_Draw(struct FIDE *fide)
{

    // draw text and cursor
    if(fide->text!=NULL)
    {
        _FIDE_MoveCursor(fide);
        _FIDE_Input(fide);
        _FIDE_DrawText(fide);
    }
}

void FIDE_Free(struct FIDE *fide)
{
    //if(fide->text!=NULL) free(fide->text);
}
