#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "error.h"
#include "utils.h"
#include "game.h"
#include "events.h"
#include "update.h"
#include "draw.h"

Game* createGame(){
    Game* p = malloc(sizeof(Game));
    if(p == NULL){
        RAGE_QUIT(1, "Malloc Game failed");
    }
    p->events.keyEvt    = NULL;
    p->events.padEvt    = NULL;
    p->events.mouseEvt  = NULL;
    p->events.key_dev   = NULL;
    p->events.mouse_dev = NULL;
    p->events.pad_dev   = NULL;

    // Open config file and open devices (root or sudo is required)
    FILE* pCfg = fopen("../config/events.cfg", "r");
    if (pCfg != NULL) {
        char tmp1[256] = {0};
        char tmp2[256] = {0};
/*
        while (fscanf(pCfg, "%[^;];%s\n", tmp1, tmp2) == 2) {
            if(strcmp(tmp1, "KEYBOARD") == 0) {
                p->events.key_dev = fopen(tmp2, "rb");
                if(p->events.key_dev == NULL) {
                    RAGE_QUIT(90, "Keyboard file opening : %s", strerror(errno));
                }
            }
            else if(strcmp(tmp1, "MOUSE") == 0){
                p->events.mouse_dev = fopen(tmp2, "rb");
                if(p->events.key_dev == NULL) {
                    RAGE_QUIT(90, "Mouse file opening : %s", strerror(errno));
                }
            }
        }
//*/
    }
    printf("%s\n", strerror(errno));

    p->pData = NULL;

    return p;
}

void setCallbacks(Game* p, EvtCallback cbKey, EvtCallback cbPad, EvtCallback cbMouse) {
    p->events.keyEvt   = cbKey;
    p->events.padEvt   = cbPad;
    p->events.mouseEvt = cbMouse;
    checkGame(p);
}

void setData(Game* p, void* pData) {
    checkGame(p);
    p->pData = pData;
}

void checkGame(Game* p){
    if(p == NULL){
        RAGE_QUIT(1, "Game pointer is NULL");
    }
    
}

long frame(Game* pGame, long nb_usec){
    // Locals
    int   quit   = 0;
    float nb_sec = nb_usec/1000000.0;
    // Check
    checkGame(pGame);
    // events-update-draw
    handleEvents(pGame);
    quit = update(pGame, nb_sec);
    draw(pGame, nb_sec);
    // Return if we have to stop the game or not
    return quit;
}

void gameLoop(Game* pGame){
    // Locals
    long start = 0;
    long prev  = 0;
    long end   = 0;
    long delta = 0;
    long diff  = 0;
    int  quit  = 0;

    // Check
    checkGame(pGame);
    initDraw(pGame);

    // Game loop    
    do{        
        start = gettime();
        delta = start - prev;
        prev  = start;
        // Frame process (events, update, draw)
        quit  = frame(pGame, delta);
        // Wait to keep a 60FPS rate
        end  = gettime();
        diff = end - start;
        if(diff < 16666){
            usleep(16666 - diff);            
        }
    } while(quit == 0);
}

