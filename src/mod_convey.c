#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_convey.h"
#include "error.h"

void conveyUpdate(Module* p) {
    fprintf(stderr, "update convey {%s}\n", p->pName);
}

void conveyDraw  (Module* p) {
    if (p != NULL) {
        printf("\x1B[%d;%dH", p->y0, p->x0);
        printf("⬜");
        for (int i=1;i<p->w-1;i++) {
            printf("🟦");
        }
        printf("⬜");
    }
    printf("\n");
}

// LIFO push
Module* addConveyModule(Module* pList, char* name, int x0, int y0, int w, int h) {
    Module* p = createModule(name, conveyUpdate, conveyDraw);
    if (p == NULL) {
        RAGE_QUIT(70, "create convey failed");
    }
    p->x0 = 2*x0;
    p->y0 = y0;
    p->w  = w;
    p->h  = h;
    p->pNext = pList;
    return p;
}
