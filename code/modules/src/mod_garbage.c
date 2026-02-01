#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_power_supply.h"
#include "error.h"
#include "user_data.h"
#include "product.h"

//=========================================================
// UPDATE callback
//=========================================================
void garbageUpdate(Module* p, void* pData) {
    if (p == NULL || pData == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
    Product* pProd = ((UserData*)pData)->products;
    while (pProd != NULL) {
        if (p->x0 <= pProd->x && pProd->x <= p->x0+2*2 && p->y0 <= pProd->y && pProd->y <= p->y0+2) {
            fprintf(stderr, "product garbage %d/%d/%d\n", pProd->x, pProd->y, pProd->toDestroy);
            pProd->toDestroy = 2;
        }
        pProd = pProd->pNext;
    }
    //*/
}

//=========================================================
// DRAW callback
//=========================================================
void garbageDraw  (Module* p) {
    if (p != NULL) {
        for (int y=0; y<p->size; y++) {
            printf("\x1B[%d;%dH", p->y0 + y, p->x0);
            for (int x=0; x<p->size; x++) {
                // border
                if (x==1 && y==p->size-1) {
                    printf("🟦");
                }
                else if (x == 0 || y == 0 || x == p->size-1 || y == p->size-1) {
                    printf("⬛");
                }
                else {
                    printf("♻️ ");
                }
            }
        }
    }
}

//=========================================================
// ACTION callback
//=========================================================
void garbageAction(Module* p, char* action) {
    if (p == NULL || action == NULL) {
        RAGE_QUIT(61, "Module or string pointer null");
    }

}

//=========================================================
// CONSTRUCTOR
//=========================================================
Module* addGarbageModule(Module* pList, char* name, int x0, int y0) {
    Module* p = createModule(name, x0, y0, 3, MOD_UP, 0.5, garbageUpdate, garbageDraw, garbageAction);
    if (p == NULL) {
        RAGE_QUIT(70, "create convey failed");
    }
    p->running = 1;
    p->powerId = 1;
    p->pNext   = pList;
    return p;
}
