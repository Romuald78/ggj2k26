#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module.h"
#include "error.h"

Module* createModule(char* name,
                     int x0, int y0, int size, int orient, float speed,
                     ModuleUpdate upd, ModuleDraw draw, ModuleAction action) {
    Module* pMod = NULL;

    if (name == NULL || upd == NULL || draw == NULL) {
        RAGE_QUIT(80, "Null input pointer");
    }
    // Zero everywhere
    pMod = calloc(1, sizeof(Module));
    if (pMod==NULL) {
        RAGE_QUIT(80, "MAlloc Module failed");
    }
    // Fill name
    strcpy(pMod->pName, name);
    // transform
    pMod->x0     = 2 * x0;
    pMod->y0     = y0;
    pMod->size   = size;
    pMod->orient = orient;
    pMod->speed  = speed;
    // Callbacks
    pMod->pUpdate = upd;
    pMod->pDraw   = draw;
    pMod->pAction = action;
    return pMod;
}


