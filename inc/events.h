#ifndef EVT_H
#define EVT_H

#include "game.h"

enum {
    LEFT  = 1,
    RIGHT = 2,
    UP    = 3,
    DOWN  = 4
};

int handleKeyEvt  (int evt_num, int evt_state, void* p);
int handlePadEvt  (int evt_num, int evt_state, void* p);
int handleMouseEvt(int evt_num, int evt_state, void* p);

void handleEvents(Game* p);

#endif

