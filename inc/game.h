#ifndef GAME_H
#define GAME_H

#include <stdio.h>

#define MAX_BUFFER_CMD 64

typedef struct {
    char buffer[MAX_BUFFER_CMD+1];
    int  index;
} Cmd;

typedef int (*EvtCallback)(int evt_num, int evt_state, void* p);

typedef struct{
    EvtCallback keyEvt;    
    EvtCallback padEvt;    
    EvtCallback mouseEvt;
    FILE*       mouse_dev;
    FILE*       key_dev;
    FILE*       pad_dev;
} EvtCallbacks;

typedef struct{
    Cmd command;
    EvtCallbacks events;
    void*        pData;
} Game;

Game* createGame();
void  setCallbacks(Game* p, EvtCallback cbKey, EvtCallback cbPad, EvtCallback cbMouse);
void setData(Game* p, void* pData);
void  checkGame(Game* p);
long  frame(Game* pGame, long deltatime);
void  gameLoop(Game* pGame);

#endif
