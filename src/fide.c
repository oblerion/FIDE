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

void FIDE_ForwardCursor(struct FIDE *fide)
{
    int tmp_pos = fide->cursor.pos;
    if(tmp_pos+1<fide->max_size)
    {
        //fide->cursor.pos++;
        if(fide->text[fide->cursor.pos+1]!='\n')
        {
            fide->cursor.x += MeasureText(
                TextFormat("%c",fide->text[fide->cursor.pos+1]),
                fide->font_size);
            fide->cursor.pos++;
        }
        else 
        {
            fide->cursor.x = 0;
            fide->cursor.y += fide->font_size*0.5f;
            fide->cursor.pos++;
        }
    }
}

void FIDE_BackwardCursor(struct FIDE *fide)
{
    int tmp_pos = fide->cursor.pos;
    if(tmp_pos-1>0)
    {
        if(fide->text[fide->cursor.pos-1]!='\n')
        {
            fide->cursor.x += MeasureText(
                TextFormat("%c",fide->text[fide->cursor.pos-1]),
                fide->font_size);
            fide->cursor.pos--;           
        }
        else
        {
            fide->cursor.x = 0;
            fide->cursor.y -= fide->font_size*0.5f;
            fide->cursor.pos--;
        }
    }
}


void FIDE_Draw(struct FIDE *fide)
{
    const int offx = 20;
    const int offy = 10;
    const int size = strlen(fide->text);
    int tmp_pos=0;
    int lx=0;
    int ly=0;
    // draw text and cursor
    if(fide->text!=NULL)
    {
        if(IsKeyPressed(KEY_RIGHT))
            FIDE_ForwardCursor(fide);
        else if(IsKeyPressed(KEY_LEFT))
            FIDE_BackwardCursor(fide);

        for(int i=0;i<size;i++)
        {
            if(fide->text[i]=='\n')
            {
                const char* cstr = strsub(fide->text,tmp_pos,i);
                DrawText(cstr,offx+lx,offy+ly,fide->font_size,BLACK);
                tmp_pos=i;
                ly += fide->font_size*0.5f;
                if(strlen(cstr)==0) ly += fide->font_size*0.5f;
            }
        }
        CURSOR_draw(&fide->cursor,offx,offy,fide->font_size);
    }
}

void FIDE_Free(struct FIDE *fide)
{
    //if(fide->text!=NULL) free(fide->text);
}
