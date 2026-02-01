#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_push.h"
#include "error.h"
#include "user_data.h"
#include "product.h"

//=========================================================
// UPDATE callback
//=========================================================
void pushUpdate(Module* p, void* pData) {
    if (p == NULL || pData == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }

    if (p->specific_mode == 2) {
        // check presence of product
        Product* pProd = ((UserData*)pData)->products;
        while (pProd != NULL) {
            // check if the product is in the module area
            int x2 = p->x0;
            int y2 = p->y0;

            // fprintf(stderr, "mod %s : x0=%d / y0=%d orient=%d\n", p->pName, p->x0, p->y0, p->orient);
            // fprintf(stderr, "         PX=%d / PY=%d\n", pProd->x, pProd->y);

            if (p->x0 <= pProd->x && pProd->x <= p->x0+2*2 && p->y0 <= pProd->y && pProd->y <= p->y0+2) {
                switch (p->orient) {
                    case MOD_LEFT:
                        x2 -= 1 * 2;
                        y2 += 1;
                        break;
                    case MOD_RIGHT:
                        x2 += 3 * 2;
                        y2 += 1;
                        break;
                    case MOD_UP:
                        x2 += 1 * 2;
                        y2 -= 1;
                        break;
                    case MOD_DOWN:
                        x2 += 1 * 2;
                        y2 += 3;
                        break;
                }

                pProd->x = x2;
                pProd->y = y2;
                p->specific_mode = 1;
            }
            fprintf(stderr, "         x2=%d / y2=%d\n", x2, y2);
            pProd = pProd->pNext;
        }
    }
    else if (p->orient == MOD_UP || p->orient == MOD_DOWN){
        Product* pProd = ((UserData*)pData)->products;
        while (pProd != NULL) {
            if (pProd->x == p->x0) {
                pProd->x = p->x0+3*2;
            }
            else if (pProd->x == p->x0+2*2) {
                pProd->x = p->x0-1*2;
            }
            pProd = pProd->pNext;
        }
    }
    else if (p->orient == MOD_LEFT || p->orient == MOD_RIGHT){
//        fprintf(stderr, "update internal PUSH '%s' orient=%d time=%f \n", p->pName, p->orient, p->time);
        Product* pProd = ((UserData*)pData)->products;
        while (pProd != NULL) {
            if (pProd->y == p->y0) {
                pProd->y = p->y0+3;
            }
            else if (pProd->y == p->y0+2) {
                pProd->y = p->y0-1;
            }
            pProd = pProd->pNext;
        }
    }
}

//=========================================================
// DRAW callback
//=========================================================
void pushDraw  (Module* p) {
    if (p != NULL) {
        printf("\x1B[%d;%dH", p->y0, p->x0);
        if (p->specific_mode == 2 && p->orient == MOD_UP) {
            printf("🟫🔼🟫");
        }
        else if (p->orient == MOD_DOWN) {
            printf("🟫🔽🟫");
        }
        else{
            printf("🟫🟦🟫");
        }

        printf("\x1B[%d;%dH", p->y0+1, p->x0);
        if (p->specific_mode == 2 && p->orient == MOD_LEFT) {
            printf("◀️ ◀️ ◀️ ");
        }
        else if (p->specific_mode == 2 && p->orient == MOD_RIGHT) {
            printf("▶️▶️▶️");
        }
        else if (p->specific_mode == 2 && p->orient == MOD_UP) {
            printf("🟦🔼🟦");
        }
        else if (p->specific_mode == 2 && p->orient == MOD_DOWN) {
            printf("🟦🔽🟦");
        }
        else if (p->orient == MOD_LEFT) {
            printf("🟦🟫◀️");
        }
        else if (p->orient == MOD_RIGHT) {
            printf("▶️🟫🟦");
        }
        else {
            printf("🟦🟫🟦");
        }
        printf("\x1B[%d;%dH", p->y0+2, p->x0);
        if (p->specific_mode == 2 && p->orient == MOD_DOWN) {
            printf("🟫🔽🟫");
        }
        else if (p->orient == MOD_UP) {
            printf("🟫🔼🟫");
        }
        else{
            printf("🟫🟦🟫");
        }


    }

}

//=========================================================
// ACTION callback
//=========================================================
void pushAction(Module* p, char* action) {
    if (p == NULL || action == NULL) {
        RAGE_QUIT(61, "Module or string pointer null");
    }
    // compare strings
    if (!strcmp("OPEN", action) || !strcmp("MARK", action) || !strcmp("EJECT", action) || !strcmp("CLEAN", action)) {
        p->specific_mode = 2;
    }
}

//=========================================================
// CONSTRUCTOR
//=========================================================
Module* addPushModule(Module* pList, char* name, int x0, int y0, int orient, float speed) {
    Module* p = createModule(name, x0, y0, 5, orient, speed, pushUpdate, pushDraw, pushAction);
    if (p == NULL) {
        RAGE_QUIT(70, "create deliver failed");
    }
    p->running = 1;
    p->specific_mode = 1;
    p->pNext         = pList;
    return p;
}
