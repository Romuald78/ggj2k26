#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_convey.h"
#include "error.h"

//=========================================================
// UPDATE callback
//=========================================================
void conveyUpdate(Module* p) {
    if (p == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
}

//=========================================================
// DRAW callback
//=========================================================
void conveyDraw  (Module* p) {
    if (p != NULL) {
        printf("\x1B[%d;%dH⬜", p->y0, p->x0);
        for (int i=1;i<p->size-1;i++) {
            if (p->orient%2 == 1) {
                printf("\x1B[%d;%dH", p->y0+i, p->x0);
            }
            int way = 1;
            if (p->orient>=2) {
                way = -1;
            }
            if (((int)(p->time/p->speed)-(way*i))%4 == 0) {
                // print arrow
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
            }
            else {
                // print normal cell
                printf("🟦");
            }
        }
        if (p->orient%2 == 1) {
            printf("\x1B[%d;%dH", p->y0+p->size-1, p->x0);
        }
        printf("⬜");
    }
}

//=========================================================
// ACTION callback
//=========================================================
void conveyAction(Module* p, char* action) {
    if (p == NULL || action == NULL) {
        RAGE_QUIT(61, "Module or string pointer null");
    }
    // compare strings
    if (!strcmp("STOP", action)) {
        p->running = 0;
    }
    else if (!strcmp("START", action)) {
        p->running = 1;
    }
}

//=========================================================
// CONSTRUCTOR
//=========================================================
Module* addConveyModule(Module* pList, char* name, int x0, int y0, int size, int orient, float speed) {
    Module* p = createModule(name, x0, y0, size, orient, speed, conveyUpdate, conveyDraw, conveyAction);
    if (p == NULL) {
        RAGE_QUIT(70, "create convey failed");
    }
    p->x0      = 2*x0;
    p->y0      = y0;
    p->size    = size;
    p->orient  = orient;
    p->speed   = speed;
    p->running = 0;
    p->pNext   = pList;
    return p;
}
