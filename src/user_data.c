#include <stdio.h>
#include "game.h"
#include "user_data.h"

#include <stdlib.h>

#include "error.h"
#include "parameters.h"
#include "product.h"
#include "utils.h"


void initUser(UserData* p) {
    p->w = SCREEN_W;
    p->h = SCREEN_H;
    p->modules  = NULL;
    p->actions  = NULL;
    p->products = NULL;
}

int updateUser(Game* pGame, float delta) {
    checkGame(pGame);
    UserData* p = (UserData*)(pGame->pData);

    // Update all modules
    Module* current_mod = p->modules;
    while (current_mod != NULL){
        // Update module timer
        if (current_mod->running) {
            current_mod->time += delta;
            if (current_mod->speed > 0) {
                while (current_mod->time >= current_mod->speed) {
                    current_mod->time -= current_mod->speed;
                    current_mod->time_step += 1;
                    // Update specific module behaviour
                    current_mod->pUpdate(current_mod, p);
                }
            }
        }

        // Go to next module
        current_mod = current_mod->pNext;
    }
    return 0;
}

void drawUser(Game* pGame) {
    checkGame(pGame);
    UserData* p = (UserData*)(pGame->pData);

    // Draw modules
    Module* current_mod = p->modules;
    while (current_mod != NULL){
        current_mod->pDraw(current_mod);
        current_mod = current_mod->pNext;
    }

    // Draw Products
    Product* current_prod = p->products;
    while (current_prod != NULL){
        printf("\x1B[%d;%dH", current_prod->y, current_prod->x);
        printBase(current_prod->type);
        current_prod = current_prod->pNext;
    }


    // set cursor at the bottom of the screen
    printf("\x1B[%d;1H\n", p->h);
}

char* updateCommand(Cmd* pCmd, char c) {
    char* res = NULL;
    if (pCmd == NULL) {
        RAGE_QUIT(90, "Update commande null pointer");
    }
    // if (c == '\n') {
    //     c = '\0';
    // }
    if (pCmd->index < MAX_BUFFER_CMD - 1) {
        pCmd->buffer[pCmd->index] = c;
        pCmd->index++;
        pCmd->buffer[pCmd->index] = '\0';
    }

    if (c == '\n') {
        res = pCmd->buffer;
        // remove line feed
        pCmd->buffer[pCmd->index-1] = '\0';
        //fprintf(stderr, "found   : |%s|\n", pCmd->buffer);
    }
    return res;
}

void flushCommand(Cmd* pCmd) {
    // remove chars until next '\0'
    int idx = 0;
    while (idx < MAX_BUFFER_CMD && pCmd->buffer[idx] != '\n') {
        idx++;
    }
    // copy from idx to MAX_BUFFER_CMD at the very beginning of the buffer
    for (int i=0; i<MAX_BUFFER_CMD; i++) {
        if (idx+i < MAX_BUFFER_CMD) {
            pCmd->buffer[i] = pCmd->buffer[idx+i];
        }
        else {
            pCmd->buffer[i] = '\0';
        }
    }
    pCmd->index = 0;
    pCmd->buffer[MAX_BUFFER_CMD] = '\0';
    //fprintf(stderr, "flushed : |%s|\n", pCmd->buffer);
}
