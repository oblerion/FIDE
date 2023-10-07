/*******************************************************************************************
*
*   Filesaving v1.0.0 - filesaving gui
*
*   MODULE USAGE:
*       #define GUI_FILESAVING_IMPLEMENTATION
*       #include "gui_filesaving.h"
*
*       INIT: GuiFilesavingState state = InitGuiFilesaving();
*       DRAW: GuiFilesaving(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 oblerion industries. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_FILESAVING_H
#define GUI_FILESAVING_H

typedef struct {
    bool fileDialogActive;
    bool pathEditMode;
    char pathText[128];
    bool fileNameEditMode;
    char fileNameText[128];
    bool fileTypeEditMode;
    int fileTypeActive;
    Rectangle ScrollPanel009ScrollView;
    Vector2 ScrollPanel009ScrollOffset;
    Vector2 ScrollPanel009BoundsOffset;

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiFilesavingState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiFilesavingState InitGuiFilesaving(void);
void GuiFilesaving(GuiFilesavingState *state);
static void DirBack();
static void FileSelect();
static void FileCancel();

#ifdef __cplusplus
}
#endif

#endif // GUI_FILESAVING_H

/***********************************************************************************
*
*   GUI_FILESAVING IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_FILESAVING_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiFilesavingState InitGuiFilesaving(void)
{
    GuiFilesavingState state = { 0 };

    state.fileDialogActive = true;
    state.pathEditMode = false;
    strcpy(state.pathText, "C:\GitHub\raysan5\rguilayout\layouts\");
    state.fileNameEditMode = false;
    strcpy(state.fileNameText, "file_dialog.rlg");
    state.fileTypeEditMode = false;
    state.fileTypeActive = 0;
    state.ScrollPanel009ScrollView = (Rectangle){ 0, 0, 0, 0 };
    state.ScrollPanel009ScrollOffset = (Vector2){ 0, 0 };
    state.ScrollPanel009BoundsOffset = (Vector2){ 0, 0 };

    // Custom variables initialization

    return state;
}
static void DirBack()
{
    // TODO: Implement control logic
}
static void FileSelect()
{
    // TODO: Implement control logic
}
static void FileCancel()
{
    // TODO: Implement control logic
}


void GuiFilesaving(GuiFilesavingState *state)
{
    const char *fileDialogText = "#005#File Select Dialog";
    const char *dirBackText = "<";
    const char *lblFileNameText = "File name:";
    const char *fileSelectText = "#005#Select";
    const char *fileCancelText = "#009#Cancel";
    const char *fileTypeText = "IMAGE (.png);STYLE (.rgs);CODE (.h)";
    const char *Label012Text = "File filter:";
    
    if (state->fileTypeEditMode) GuiLock();

    if (state->fileDialogActive)
    {
        state->fileDialogActive = !GuiWindowBox((Rectangle){ 48, 48, 480, 300 }, fileDialogText);
        if (GuiButton((Rectangle){ 472, 80, 48, 24 }, dirBackText)) DirBack(); 
        if (GuiTextBoxMulti((Rectangle){ 56, 80, 408, 24 }, state->pathText, 128, state->pathEditMode)) state->pathEditMode = !state->pathEditMode;
        GuiLabel((Rectangle){ 56, 280, 64, 24 }, lblFileNameText);
        if (GuiTextBoxMulti((Rectangle){ 120, 280, 280, 24 }, state->fileNameText, 128, state->fileNameEditMode)) state->fileNameEditMode = !state->fileNameEditMode;
        if (GuiButton((Rectangle){ 408, 280, 112, 24 }, fileSelectText)) FileSelect(); 
        if (GuiButton((Rectangle){ 408, 312, 112, 24 }, fileCancelText)) FileCancel(); 
        GuiLabel((Rectangle){ 56, 312, 64, 24 }, Label012Text);
        GuiScrollPanel((Rectangle){ 56, 112, 464 - state->ScrollPanel009BoundsOffset.x, 160 - state->ScrollPanel009BoundsOffset.y }, ScrollPanel009Text, (Rectangle){ 56, 112, 464, 160 }, &state->ScrollPanel009ScrollOffset, &state->ScrollPanel009ScrollView);
        if (GuiDropdownBox((Rectangle){ 120, 312, 280, 24 }, fileTypeText, &state->fileTypeActive, state->fileTypeEditMode)) state->fileTypeEditMode = !state->fileTypeEditMode;
    }
    
    GuiUnlock();
}

#endif // GUI_FILESAVING_IMPLEMENTATION
