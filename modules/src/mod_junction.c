#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/mod_junction.h"
#include "error.h"

void junctionUpdate(Module* p) {
    if (p == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
    // increase time
    p->time += 1;
    p->time &= 0x7FFFFFFF;
}

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

// LIFO push
Module* addJunctionModule(Module* pList, char* name, int x0, int y0, int orient){
    Module* p = createModule(name, junctionUpdate, junctionDraw);
    if (p == NULL) {
        RAGE_QUIT(60, "create junction failed");
    }
    p->x0 = 2*x0;
    p->y0 = y0;
    p->size  = 3;
    p->orient  = orient;
    p->speed = 1;
    p->pNext = pList;
    return p;
}
