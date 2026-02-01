#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod_paint.h"
#include "error.h"
#include "user_data.h"
#include "product.h"

//=========================================================
// UPDATE callback
//=========================================================

char* getRandomBad() {
    if ( rand()%101 <= 50) {
        return "💩";
    }
    else {
        return "🤮";
    }
}

char* getColorMask1(int clr) {
    switch (clr) {
        case WHITE:
            return "💀";
        case BLACK:
            return "🦇";
        case RED:
            return "👺";
        case ORANGE:
            return "👹";
        case YELLOW:
            return "🥸";
        case GREEN:
            return "👽";
        case BLUE:
            return "🥶";
        case PURPLE:
            return "👾";
        default:
            return getRandomBad();
    }
}

void paintUpdate(Module* p, void* pData) {
    if (p == NULL || pData == NULL) {
        RAGE_QUIT(60, "Module pointer null");
    }

    //*
    Product* pProd = ((UserData*)pData)->products;
    while (pProd != NULL) {
        if (p->x0 <= pProd->x && pProd->x <= p->x0 + 4*2 && p->y0 <= pProd->y  && pProd->y <= p->y0+4) {
            if(p->specific_mode % 2 == 1) {
                if (strcmp(pProd->type, "👤") == 0) {
                    pProd->type = getColorMask1(p->color);
                }
            }
            else  {
                if (strcmp(pProd->type, "👥") == 0) {
                    // TODO  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! !!!!
                }
                else {
                    pProd->type = getRandomBad();
                }
            }
            pProd->x += 5 * 2;
        }
        pProd = pProd->pNext;
    }
    //*/


}

//=========================================================
// DRAW callback
//=========================================================
char* getColorStr(int clr) {
    switch (clr) {
        case WHITE:
            return "⚪";
        case BLACK:
            return "⚫";
        case RED:
            return "🔴";
        case ORANGE:
            return "🟠";
        case YELLOW:
            return "🟡";
        case GREEN:
            return "🟢";
        case BLUE:
            return "🔵";
        case PURPLE:
            return "🟣";
        default:
        case NONE:
            return "✖️ ";
    }
}

void paintDraw  (Module* p) {
    if (p != NULL) {

        char* clr  = getColorStr(p->color);
        char* clr2 = getColorStr(p->color2);


        printf("\x1B[%d;%dH", p->y0, p->x0);
        printf("🟩🟩🟩🟩🟩");
        printf("\x1B[%d;%dH", p->y0+1, p->x0);
        if (p->specific_mode == 1) {
            printf("🟩⬛🖌️ ⬛🟩");
            printf("\x1B[%d;%dH", p->y0+2, p->x0);
            printf("🟦⬛%s⬛🟦", clr);
        }
        else {
            printf("🟩🖌️ ⬛🖌️ 🟩");
            printf("\x1B[%d;%dH", p->y0+2, p->x0);
            printf("🟦%s⬛%s🟦", clr, clr2);
        }
        printf("\x1B[%d;%dH", p->y0+3, p->x0);
        printf("🟩🟩🟩🟩🟩");
    }
}

//=========================================================
// ACTION callback
//=========================================================
void paintAction(Module* p, char* action) {
    if (p == NULL || action == NULL) {
        RAGE_QUIT(61, "Module or string pointer null");
    }
    // compare strings
    if (!strcmp("PAINT", action)) {
        p->specific_mode = !p->specific_mode;
    }
    else {
        int tmp = p->color;
        if (!strcmp("NONE", action)) {
            p->color  = NONE;
            p->color2 = NONE;
            tmp = NONE;
        }
        else if (!strcmp("WHITE", action)) {
            p->color = WHITE;
        }
        else if (!strcmp("BLACK", action)) {
            p->color = BLACK;
        }
        else if (!strcmp("RED", action)) {
            p->color = RED;
        }
        else if (!strcmp("ORANGE", action)) {
            p->color = ORANGE;
        }
        else if (!strcmp("YELLOW", action)) {
            p->color = YELLOW;
        }
        else if (!strcmp("GREEN", action)) {
            p->color = GREEN;
        }
        else if (!strcmp("BLUE", action)) {
            p->color = BLUE;
        }
        else if (!strcmp("PURPLE", action)) {
            p->color = PURPLE;
        }
        else {
            return;
        }
        p->color2 = tmp;
    }
}

//=========================================================
// CONSTRUCTOR
//=========================================================
Module* addPainterModule(Module* pList, char* name, int x0, int y0, float speed) {
    Module* p = createModule(name, x0, y0, 5, MOD_LEFT, speed, paintUpdate, paintDraw, paintAction);
    if (p == NULL) {
        RAGE_QUIT(101, "create paint failed");
    }
    p->running = 1;
    p->specific_mode = MOD_BASE_1;
    p->pNext = pList;
    return p;
}
