#pragma once
#include "raylib.h"
#include "ui.h"

struct IDE_PARAMETER
{
    bool visible;
};
struct IDE_PARAMETER IDE_PARAMETER();
void IDE_PARAMETER_draw(struct IDE_PARAMETER* idepara);