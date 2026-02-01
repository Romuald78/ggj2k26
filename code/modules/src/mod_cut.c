#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_cut.h"
#include "error.h"
#include "user_data.h"
#include "product.h"

//=========================================================
// UPDATE callback
//=========================================================
void cutterUpdate(Module* p, void* pData) {
    if (p == NULL || pData == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
}

//=========================================================
// DRAW callback
//=========================================================
void cutterDraw  (Module* p) {
    if (p != NULL) {
        printf("\x1B[%d;%dH", p->y0, p->x0);
        printf("🟩🟩🟩🟩🟩");
        printf("\x1B[%d;%dH", p->y0+1, p->x0);
        printf("🟩⬛⬛⬛🟩");
        printf("\x1B[%d;%dH", p->y0+2, p->x0);
        if (p->specific_mode == 1) {
            printf("🟦⬛✂️ ⬛🟦");
        }
        else {
            printf("🟦✂️ ⬛✂️ 🟦");
        }
        printf("\x1B[%d;%dH", p->y0+3, p->x0);
        printf("🟩⬛⬛⬛🟩");
        printf("\x1B[%d;%dH", p->y0+4, p->x0);
        printf("🟩🟩🟩🟩🟩");
    }
}

//=========================================================
// ACTION callback
//=========================================================
void cutterAction(Module* p, char* action) {
    if (p == NULL || action == NULL) {
        RAGE_QUIT(61, "Module or string pointer null");
    }
    // compare strings
    if (!strcmp("xxxxx", action)) {
        p->running = 1;
    }
    else if (!strcmp("xxxffxx", action)) {
        p->running = 0;
    }
}

//=========================================================
// CONSTRUCTOR
//=========================================================
Module* addCutterModule(Module* pList, char* name, int x0, int y0, float speed) {
    Module* p = createModule(name, x0, y0, 5, MOD_RIGHT, speed, cutterUpdate, cutterDraw, cutterAction);
    if (p == NULL) {
        RAGE_QUIT(70, "create convey failed");
    }
    p->specific_mode = MOD_BASE_1;
    p->pNext = pList;
    return p;
}
