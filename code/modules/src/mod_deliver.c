#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_deliver.h"
#include "error.h"
#include "user_data.h"
#include "product.h"

//=========================================================
// UPDATE callback
//=========================================================
void deliverUpdate(Module* p, void* pData) {
    if (p == NULL || pData == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
}

//=========================================================
// DRAW callback
//=========================================================
void deliverDraw  (Module* p) {
    if (p != NULL) {
        printf("\x1B[%d;%dH", p->y0+4, p->x0);
        printf("⬛⬛⬛⬛⬛");
    }
}

//=========================================================
// ACTION callback
//=========================================================
void deliverAction(Module* p, char* action) {
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
Module* addDeliverModule(Module* pList, char* name, int x0, int y0, float speed) {
    Module* p = createModule(name, x0, y0, 5, MOD_LEFT, speed, deliverUpdate, deliverDraw, deliverAction);
    if (p == NULL) {
        RAGE_QUIT(70, "create deliver failed");
    }
    p->pNext = pList;
    return p;
}
