//
// Created by cytech on 26/01/2026.
//

#ifndef GGJ2K26_V3_ACTION_H
#define GGJ2K26_V3_ACTION_H

#include "module.h"


typedef struct _act {
    char         pName[32];  // action name
    Module*      pMod;
    struct _act* pNext;
} Action;

Action* addAction(Action* pList, char* actname, Module* pMod);

#endif //GGJ2K26_V3_ACTION_H