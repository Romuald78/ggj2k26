#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_junction.h"
#include "error.h"
#include "user_data.h"

//=========================================================
// UPDATE callback
//=========================================================
void junctionUpdate(Module* p, void* pData) {
    if (p == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
    // Process all goods located in the current module (2D area)
    Product* pProd = ((UserData*)pData)->products;
    while (pProd != NULL){
        //fprintf(stderr,"[%s] x=%d/y=%d/p->x0=%d/p->y0=%d\n", p->pName, pProd->x, pProd->y, p->x0, p->y0);
        // is it inside junction ?
        if(p->x0-2 <= pProd->x && pProd->x <= p->x0+2 && p->y0-1 <= pProd->y && pProd->y <= p->y0+1) {
            int x2 = p->x0;
            int y2 = p->y0;
            // is it in the middle ?
            if (pProd->x == p->x0 && pProd->y == p->y0) {
                switch (p->orient) {
                    case MOD_LEFT:
                        x2 -= 2 * 2;
                        break;
                    case MOD_RIGHT:
                        x2 += 2 * 2;
                        break;
                    case MOD_UP:
                        y2 -= 2 ;
                        break;
                    case MOD_DOWN:
                        y2 += 2;
                        break;
                }
            }
            // if the product was not in the middle it will be placed , and then, on the next update
            // the product will be ejected
            pProd->x = x2;
            pProd->y = y2;
        }
        pProd = pProd->pNext;
    }
}

//=========================================================
// DRAW callback
//=========================================================
void junctionDraw  (Module* p) {
    if (p != NULL) {
        printf("\x1B[%d;%dH", p->y0-1, p->x0-2);
        printf("⬛🟦⬛");
        printf("\x1B[%d;%dH", p->y0+1, p->x0-2);
        printf("⬛🟦⬛");
        printf("\x1B[%d;%dH", p->y0, p->x0-2);
        printf("🟦");
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
        printf("🟦");
    }
}

//=========================================================
// ACTION callback
//=========================================================
void junctionAction(Module* pMod, char* actname) {
    if (pMod == NULL || actname == NULL) {
        RAGE_QUIT(61, "Module or string pointer null");
    }
    // compare strings
    if (!strcmp("TURNLEFT", actname)) {
        pMod->orient += MOD_NB_DIRS - 1;
        pMod->orient %= MOD_NB_DIRS;
    }
    else if (!strcmp("TURNRIGHT", actname)) {
        pMod->orient += 1;
        pMod->orient %= MOD_NB_DIRS;
    }
}

//=========================================================
// CONSTRUCTOR
//=========================================================
Module* addJunctionModule(Module* pList, char* name, int x0, int y0, int orient, float speed){
    Module* p = createModule(name, x0, y0, 3, orient, speed, junctionUpdate, junctionDraw, junctionAction);
    if (p == NULL) {
        RAGE_QUIT(60, "create junction failed");
    }
    // By default, the junctions are always running
    p->running = 1;
    p->pNext   = pList;
    return p;
}
