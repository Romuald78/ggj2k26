#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/module.h"
#include "error.h"

Module* createModule(char* name, ModuleUpdate upd, ModuleDraw draw) {
    Module* pMod = NULL;

    if (name == NULL || upd == NULL || draw == NULL) {
        RAGE_QUIT(80, "Null input pointer");
    }
    // Zero everywhere
    pMod = calloc(1, sizeof(Module));
    if (pMod==NULL) {
        RAGE_QUIT(80, "MAlloc Module failed");
    }
    strcpy(pMod->pName, name);
    pMod->pUpdate = upd;
    pMod->pDraw = draw;
    return pMod;
}


