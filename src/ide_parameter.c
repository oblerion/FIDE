#include "ide_parameter.h"

struct IDE_PARAMETER IDE_PARAMETER()
{
    struct IDE_PARAMETER idepara;
    idepara.visible=false;
    return idepara;
}

void IDE_PARAMETER_draw(struct IDE_PARAMETER *idepara)
{
    if(idepara->visible)
    {
        puts("ui parameter");
    }
}
