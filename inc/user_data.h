

#ifndef GGJ2K26_V3_USER_DATA_H
#define GGJ2K26_V3_USER_DATA_H

#include "game.h"
#include "module.h"

typedef struct {
    int zoomin;
    int zoomout;
    int w;
    int h;
    Module* modules;
} UserData;


void  initUser(UserData* p);
void  drawUser(Game* pGame);
int   updateUser(Game* pGame);
char* updateCommand(Cmd* pCmd, char c);
void  flushCommand(Cmd* pCmd);

#endif //GGJ2K26_V3_USER_DATA_H