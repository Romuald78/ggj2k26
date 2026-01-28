

#ifndef GGJ2K26_V3_USER_DATA_H
#define GGJ2K26_V3_USER_DATA_H

#include "action.h"
#include "game.h"
#include "module.h"

typedef struct {
    int w;
    int h;
    Module* modules;
    Action* actions;
} UserData;


void  initUser(UserData* p);
void  drawUser(Game* pGame);
int   updateUser(Game* pGame, float delta);
char* updateCommand(Cmd* pCmd, char c);
void  flushCommand(Cmd* pCmd);

#endif //GGJ2K26_V3_USER_DATA_H