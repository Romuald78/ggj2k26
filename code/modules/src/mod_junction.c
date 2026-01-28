#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_junction.h"
#include "error.h"

//=========================================================
// UPDATE callback
//=========================================================
void junctionUpdate(Module* p) {
    if (p == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
}

//=========================================================
// DRAW callback
//=========================================================
void junctionDraw  (Module* p) {
    if (p != NULL) {
        printf("\x1B[%d;%dH", p->y0-1, p->x0-2);
        printf("⬛⬜⬛");
        printf("\x1B[%d;%dH", p->y0+1, p->x0-2);
        printf("⬛⬜⬛");
        printf("\x1B[%d;%dH", p->y0, p->x0-2);
        printf("⬜");
        switch (p->orient) {
            case MOD_LEFT:
                printf("⬅️ ");
                break;
            case MOD_RIGHT:
                printf("➡️ ");
                break;
            case MOD_UP:
                printf("⬆️ ");
                break;
            case MOD_DOWN:
                printf("⬇️ ");
                break;
            default:
                printf("??");
                break;
        }
        printf("⬜");
    }
}

//=========================================================
// ACTION callback
//=========================================================
void junctionAction(Module* pMod, char* actname) {

}

//=========================================================
// CONSTRUCTOR
//=========================================================
Module* addJunctionModule(Module* pList, char* name, int x0, int y0, int orient){
    Module* p = createModule(name, x0, y0, 3, orient, 1, junctionUpdate, junctionDraw, junctionAction);
    if (p == NULL) {
        RAGE_QUIT(60, "create junction failed");
    }
    p->pNext   = pList;
    return p;
}
