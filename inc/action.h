//
// Created by cytech on 26/01/2026.
//

#ifndef GGJ2K26_V3_ACTION_H
#define GGJ2K26_V3_ACTION_H

#include "../src/modules/inc/module.h"

typedef void (*ModuleAction)(Module* p);


typedef struct _act {
    char         pName[32];  // action name
    Module*      pMod;
    ModuleAction pAction;
    struct _act* pNext;
} Action;

Action* addAction(Action* pList, char* pActName, char* pModName, ModuleAction pAct);

#endif //GGJ2K26_V3_ACTION_H