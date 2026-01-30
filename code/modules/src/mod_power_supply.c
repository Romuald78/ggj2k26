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
void powerUpdate(Module* p, void* pData) {
    if (p == NULL || pData == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
}

//=========================================================
// DRAW callback
//=========================================================
void powerDraw  (Module* p) {
    if (p != NULL) {
        for (int y=0; y<p->size; y++) {
            printf("\x1B[%d;%dH", p->y0 + y, p->x0);
            for (int x=0; x<p->size; x++) {
                // border
                if (x == 0 || y == 0 || x == p->size-1 || y == p->size-1) {
                    // output
                    if ( y==3 && x%3!=0){
                        if (p->running) {
                            printf("🟨");
                        }
                        else {
                            printf("🔲");
                        }
                    }
                    else {
                        // simple border
                        printf("⬛");
                    }
                }
                else if (y==1) {
                    // inner cells top
                    if (p->running) {
                        printf("🔴");
                    }
                    else {
                        printf("⚫PWRON2"
                               "PWRON2"
                               "");
                    }
                }
                else if (x==1){
                    printf("⚡");
                }
                else {
                    printf("🆕");
                }
            }
        }
    }
}

//=========================================================
// ACTION callback
//=========================================================
void powerAction(Module* p, char* action) {
    if (p == NULL || action == NULL) {
        RAGE_QUIT(61, "Module or string pointer null");
    }
    // compare strings
    if (!strcmp("PWROFF", action)) {
        p->running = 0;
    }
    else if (!strcmp("PWRON", action)) {
        p->running = 1;
    }
}

//=========================================================
// CONSTRUCTOR
//=========================================================
Module* addPowerSupModule(Module* pList, char* name, int number, int x0, int y0) {
    Module* p = createModule(name, x0, y0, 4, MOD_DOWN, 0, powerUpdate, powerDraw, powerAction);
    if (p == NULL) {
        RAGE_QUIT(70, "create convey failed");
    }
    p->powerId = number;
    p->pNext   = pList;
    return p;
}
