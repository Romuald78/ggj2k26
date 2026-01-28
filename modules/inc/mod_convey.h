//
// Created by cytech on 26/01/2026.
//

#ifndef GGJ2K26_V3_MOD_CONVEY_H
#define GGJ2K26_V3_MOD_CONVEY_H

#include "module.h"


Module* addConveyModule(Module* pList, char* name, int x0, int y0, int size, int orient, int speed);
void conveyActions(Module* p, char* action);

#endif //GGJ2K26_V3_MOD_CONVEY_H