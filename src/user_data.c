#include <stdio.h>
#include "game.h"
#include "user_data.h"

#include <stdlib.h>

#include "error.h"


void initUser(UserData* p) {
    p->w = 70;
    p->h = 33;
    p->zoomin = 0;
    p->zoomout = 0;
    p->modules = NULL;
}

int updateUser(Game* pGame) {
    checkGame(pGame);
    UserData* p = (UserData*)(pGame->pData);
    if(p) {
        if (p->zoomin) {
            p->w += 1;
        }
        if (p->zoomout) {
            p->w -= 1;
        }
    }
    return 0;
}

void drawUser(Game* pGame) {
    checkGame(pGame);
    UserData* p = (UserData*)(pGame->pData);

    // Draw border
    for (int j=0; j<p->w; j++) {
        printf("🧱");
    }
    puts("");
    for (int i=1; i<p->h-1; i++) {
        printf("🧱");
        for (int j=1; j<p->w-1; j++)   {
            printf("  ");
        }
        /*
        for (int j=1; j<p->w-1 - 11; j+=11)   {
            printf("  🧭▶️ 🔌⚙️ 📦⏱️ 🚨🛠️ 📊💡");
        }
        //*/
        puts("🧱");
    }
    for (int j=0; j<p->w; j++) {
        printf("🧱");
    }
    puts("");

    Module* current_mod = p->modules;
    while (current_mod != NULL){
        current_mod->pDraw(current_mod);
        current_mod = current_mod->pNext;
    }




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
        fprintf(stderr, "found   : |%s|\n", pCmd->buffer);
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
    fprintf(stderr, "flushed : |%s|\n", pCmd->buffer);
}
