#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_convey.h"
#include "error.h"

void conveyUpdate(Module* p) {
    if (p == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
    // increase time
    p->time += 1;
    p->time &= 0x7FFFFFFF;
}

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
            if (((p->time/p->speed)-(way*i))%3 == 0) {
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

// LIFO push
Module* addConveyModule(Module* pList, char* name, int x0, int y0, int size, int orient, int speed) {
    Module* p = createModule(name, conveyUpdate, conveyDraw);
    if (p == NULL) {
        RAGE_QUIT(70, "create convey failed");
    }
    p->x0 = 2*x0;
    p->y0 = y0;
    p->size  = size;
    p->orient  = orient;
    p->speed = speed;
    p->pNext = pList;
    return p;
}
