#include "fide.h"

#define MAX_LINEDRAW 22

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
    if(cursor->timer<0)
    {
		cursor->timer = 0.5f;
    }
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
        DrawRectangle(x,y,4,ph,cursor->color);
	}
}

struct FIDE FIDE(int pfont_size)
{
    struct FIDE fide = {
        pfont_size,
        CURSOR(),
        0,
        0,0,0
    };
 
    return fide;
}

void FIDE_Init(struct FIDE *fide)
{
    TextCopy(fide->filename,"save.txt");
    fide->text = (char*)MemAlloc(500);
    TextCopy(fide->text,"\n\0");
    fide->max_size = 500;
}

void FIDE_Load(struct FIDE *fide, const char *file)
{
    if(FileExists(file))
    {
        if(fide->text!=0){ MemFree(fide->text); fide->text=0;}
        char* text = LoadFileText(file);
        fide->text = (char*)MemAlloc(TextLength(text)+500);
        fide->text[0] = '\n';
        for(int i=0;i<TextLength(text);i++)
        {
            fide->text[i+1]=text[i];
        }
        fide->text[TextLength(text)+1]='\0';
        TextCopy(fide->filename,file);
        UnloadFileText(text);
    }
    else
    {
        FIDE_Init(fide);
    }
}

void FIDE_Save(struct FIDE fide)
{
    SaveFileText(fide.filename,fide.text);
}

int _FIDE_GetNextLine(struct FIDE* fide,int pos)
{
    int ri=pos;
    if(fide->text[ri]=='\n' && ri<TextLength(fide->text))
    {
        ri++;
    }
    for(int i=ri;i<TextLength(fide->text);i++)
    {
        if(fide->text[i]=='\n') 
        {
            ri=i;
            break;
        }
    }
    return ri;
}

int _FIDE_GetBackLine(struct FIDE* fide,int pos)
{
    int ri=pos;
    bool rpt=false;
    if(fide->text[ri]=='\n' && ri>0)
    {
        ri--;
    }
    else  rpt=true;
    for(int i=ri;i>0;i--)
    {
        if(fide->text[i]=='\n') 
        {
            if(rpt) rpt=false;
            else
            {
                ri=i;
                break;
            }
        }
        else if(i==1)
        {
            ri=0;
            break;
        }
    }
    return ri;
}

void _FIDE_MoveCursor(struct FIDE *fide)
{
    if(IsKeyPressed(KEY_RIGHT))
    {
        // pos-offset
        if(fide->cursor.pos+1 < TextLength(fide->text))
        {
            fide->cursor.pos++;
        }
        if(fide->cursor.pos<fide->offset_pos)
            fide->offset_pos = _FIDE_GetNextLine(fide,fide->offset_pos);
    }
    if(IsKeyPressed(KEY_LEFT))
    {
        if(fide->cursor.pos-fide->offset_pos<0)
            fide->offset_pos = _FIDE_GetBackLine(fide,fide->offset_pos);
        if(fide->cursor.pos>0)
        {
            fide->cursor.pos--;
        }
    }
    if(IsKeyPressed(KEY_UP) || GetMouseWheelMove()<0)
    {
        if(fide->cursor.pos-fide->offset_pos<0)
            fide->offset_pos = _FIDE_GetBackLine(fide,fide->offset_pos);
        else
            fide->cursor.pos = _FIDE_GetBackLine(fide,fide->cursor.pos);
    }
    if(IsKeyPressed(KEY_DOWN) || GetMouseWheelMove()>0)
    {
        if(fide->cursor.pos-fide->offset_pos>MAX_LINEDRAW)
            fide->offset_pos = _FIDE_GetNextLine(fide,fide->offset_pos);
        else
            fide->cursor.pos = _FIDE_GetNextLine(fide,fide->cursor.pos);
    }
}


void _FIDE_DrawText(struct FIDE *fide)
{
    const int offx = MeasureText("0000000",fide->font_size);
    const int offy = 30;

    int tmp_nb = 1; // line number
    int tmp_pos = 0; // ant pos
    int tmp_y = 0; //move in line
    
    DrawRectangleLines(offx-5,offy-5,GetScreenWidth()-(offx-5),GetScreenHeight()-(offy-5),WHITE);
    for(int i=0;i<TextLength(fide->text);i++)
    {
        if(fide->text[i]=='\n')
        {
            const char* sstr = 0;
            if(fide->cursor.pos > tmp_pos && fide->cursor.pos < i)
                sstr = TextSubtext(fide->text,tmp_pos+fide->offset_posX,i-(tmp_pos+fide->offset_posX)); 
            else 
                sstr = TextSubtext(fide->text,tmp_pos,i-tmp_pos); 

            if(i>fide->offset_pos)
            {
                DrawText(sstr,offx,offy+tmp_y,fide->font_size,BLACK);//draw text
                DrawText(TextFormat("%d",tmp_nb),2,offy+tmp_y,fide->font_size,BLACK);//draw line num
                tmp_y += fide->font_size;               
            }
            tmp_pos=i+1;
            if(i>0) tmp_nb++;
            else if(TextLength(sstr)>0) tmp_nb++;
        }
        if(i==fide->cursor.pos)
        {
            const char* before_cur = TextSubtext(fide->text,(tmp_pos+fide->offset_posX),fide->cursor.pos-(tmp_pos+fide->offset_posX)+1);      
            fide->cursor.x = MeasureText(before_cur,fide->font_size); 
            fide->cursor.y = tmp_y;      
        }
    }
    // draw last line
    const char* sstr = TextSubtext(fide->text,tmp_pos,TextLength(fide->text)-tmp_pos);
    DrawText(sstr,offx,offy+tmp_y,fide->font_size,BLACK);
    DrawText(TextFormat("%d",tmp_nb),2,offy+tmp_y,fide->font_size,BLACK);

    CURSOR_draw(&fide->cursor,offx,offy,fide->font_size);
}

void _FIDE_AddChar(struct FIDE *fide,char k)
{
    if(fide->max_size<TextLength(fide->text)+1)
    {
        const int csize = TextLength(fide->text);
        char lstr[csize];
        TextCopy(lstr,fide->text);
        lstr[csize]='\0';
        MemFree(fide->text);
        fide->text = 0;
        fide->text = (char*)MemAlloc(csize+500);
        fide->max_size = TextLength(lstr)+500;
        fide->text[fide->max_size]='\0';
        TextCopy(fide->text,lstr);
    }
  
    const int csize = TextLength(fide->text);
    fide->text[csize]='\n';
    fide->text[csize+1]='\0';
    for(int i=csize;i>fide->cursor.pos;i--)
    {
        fide->text[i] = fide->text[i-1];
    }
    fide->text[fide->cursor.pos+1]=k;
    fide->cursor.pos++;
}

void _FIDE_DelChar(struct FIDE *fide)
{
    const int lp = fide->cursor.pos;
    if(TextLength(fide->text)==1)
    {
        TextCopy(fide->text,"\0");
    }
    else if(lp>-1)
    {
        for(int i=lp;i<TextLength(fide->text);i++)
        {
            fide->text[i] = fide->text[i+1];
        } 
        fide->cursor.pos=lp-1;
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
    else if((ck>=33 && ck<=47) ||
            (ck>=58 && ck<=64) ||
            (ck>=91 && ck<=96) || 
            (ck>=123 && ck<=126))
        _FIDE_AddChar(fide,ck);

    if(IsKeyPressed(KEY_TAB))
    {
        _FIDE_AddChar(fide,'\t');
    }
    else if(IsKeyPressed(KEY_ENTER))
    {
        if(fide->cursor.pos-fide->offset_pos>MAX_LINEDRAW)
        {
            fide->offset_pos = _FIDE_GetNextLine(fide,fide->offset_pos);
           // fide->cursor.pos = _FIDE_GetBackLine(fide,fide->cursor.pos);
        }
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
    if(fide->text!=0)
    {
        _FIDE_MoveCursor(fide);
        _FIDE_Input(fide);
        _FIDE_DrawText(fide);
    }
}

void FIDE_Free(struct FIDE *fide)
{
    if(fide->text!=0)
    {
        MemFree(fide->text);
        fide->text = 0;
    }
}
