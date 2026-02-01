#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_power_supply.h"
#include "error.h"
#include "parameters.h"
#include "user_data.h"
#include "product.h"
#include "utils.h"


//=========================================================
// UPDATE callback
//=========================================================
void loaderUpdate(Module* p, void* pData) {
    if (p == NULL || pData == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }
    // get output position
    int dx = 0;
    int dy = 0;
    switch (p->orient) {
        case MOD_RIGHT:
            dx += 3;
            dy += 1;
            break;
        case MOD_DOWN:
            dx += 1;
            dy += 3;
            break;
        case MOD_LEFT:
            dx -= 1;
            dy += 1;
            break;
        case MOD_UP:
            dx += 1;
            dy -= 1;
            break;
    }
    // Check if there is a product in the loader

    if (collisionProduct( ((UserData*)pData)->products, p->x0+2*dx, p->y0+dy)) {
        return;
    }
    // no product found : create
    char* prodstr = "📦";
    if (p->specific_mode == 1) {
        prodstr = "🧻";
    }
    ((UserData*)pData)->products = addProduct( ((UserData*)pData)->products,
                                          prodstr, p->x0/2 + dx, p->y0 + dy);
}

//=========================================================
// DRAW callback
//=========================================================
void loaderDraw  (Module* p) {
    if (p != NULL) {
        switch (p->orient) {
            case MOD_RIGHT:
                printf("\x1B[%d;%dH", p->y0 + 0, p->x0);
                printf("🔼⬛⬛");
                printf("\x1B[%d;%dH", p->y0 + 1, p->x0);
                printSquareNumber(p->load_speed);
                printBase(p->specific_mode);
                printf("🟦");
                printf("\x1B[%d;%dH", p->y0 + 2, p->x0);
                printf("🔽⬛⬛");
                break;
            case MOD_DOWN:
                printf("\x1B[%d;%dH", p->y0 + 0, p->x0);
                printf("◀️ ");
                printSquareNumber(p->load_speed);
                printf("▶️");
                printf("\x1B[%d;%dH", p->y0 + 1, p->x0);
                printf("⬛");
                printBase(p->specific_mode);
                printf("⬛");
                printf("\x1B[%d;%dH", p->y0 + 2, p->x0);
                printf("⬛🟦⬛");
                break;
            case MOD_LEFT:
                printf("\x1B[%d;%dH", p->y0 + 0, p->x0);
                printf("⬛⬛🔼");
                printf("\x1B[%d;%dH", p->y0 + 1, p->x0);
                printf("🟦");
                printBase(p->specific_mode);
                printSquareNumber(p->load_speed);
                printf("\x1B[%d;%dH", p->y0 + 2, p->x0);
                printf("⬛⬛🔽");
                break;
            case MOD_UP:
                printf("\x1B[%d;%dH", p->y0 + 0, p->x0);
                printf("⬛🟦⬛");
                printf("\x1B[%d;%dH", p->y0 + 1, p->x0);
                printf("⬛");
                printBase(p->specific_mode);
                printf("⬛");
                printf("\x1B[%d;%dH", p->y0 + 2, p->x0);
                printf("◀️ ");
                printSquareNumber(p->load_speed);
                printf("▶️");
                break;
        }
    }
}

//=========================================================
// ACTION callback
//=========================================================
void loaderAction(Module* p, char* action) {
    if (p == NULL || action == NULL) {
        RAGE_QUIT(61, "Module or string pointer null");
    }
    // compare strings
    if (!strcmp("START", action) || !strcmp("RIGHT", action)) {
        p->load_speed++;
        if (p->load_speed >= 9) {
            p->load_speed = 9;
        }
        p->running = 1;
    }
    else if (!strcmp("STOP", action) || !strcmp("LEFT", action)) {
        p->load_speed--;
        if (p->load_speed <= 0) {
            p->load_speed = 0;
            p->running = 0;
        }
    }
    else if (!strcmp("TOGGLE", action)) {
        p->specific_mode++;
        if (p->specific_mode > 2) {
            p->specific_mode = 1;
        }
    }
    //--------------------------------
    p->speed = 0.0;
    if (p->load_speed > 0) {
        float ratio = (p->load_speed-1.0) / 8.0;
        p->speed = (ratio * SPEED_MAX) + ((1.0-ratio) * SPEED_MIN);
    }
}

//=========================================================
// CONSTRUCTOR
//=========================================================
Module* addLoaderModule(Module* pList, char* name, int x0, int y0, int orient, int type) {
    Module* p = createModule(name, x0, y0, 3, orient, 0, loaderUpdate, loaderDraw, loaderAction);
    if (p == NULL) {
        RAGE_QUIT(70, "create convey failed");
    }
    p->specific_mode   = type;
    p->load_speed = 0;

    p->powerId = 1;
    p->pNext   = pList;
    return p;
}
