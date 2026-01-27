#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include "events.h"

#include <string.h>

#include "user_data.h"




int handleKeyEvt(int evt_num, int evt_state, void* pData) {

    Game*     p  = (Game*)pData;
    UserData* ud = (UserData*)(p->pData);
    char* cmd = NULL;
    cmd = updateCommand(&(p->command), evt_num & 0xFF);
    if (cmd != NULL) {

        // check command
        // TODO optimize using function pointers in a list (polymorphism)
        if ( strcmp(cmd, "xxxxx") == 0 ) {
            //
        }

        // flush command to check for the next one
        flushCommand(&(p->command));
    }

    return 0;
}

int handlePadEvt(int evt_num, int evt_state, void* pData) {
    //    fprintf(stderr, "PAD\n");
    return 0;
}

int handleMouseEvt(int evt_num, int evt_state, void* pData) {
    //    fprintf(stderr, "MOUSE\n");
    return 0;
}



void handleEvents(Game* pGame){
    // Locals
    struct input_event ev;
    // check
    checkGame(pGame);
    // call event functions if needed
    if(pGame->events.keyEvt != NULL) {
        int value;
        value = getchar();
        while ( value != EOF ) {
            pGame->events.keyEvt(value, 0, pGame);
            if (ev.type == EV_KEY && ev.value <= 1) {
                pGame->events.keyEvt(ev.code, ev.value, pGame);
            }

            value = getchar();
        }

    }
    if(pGame->events.padEvt != NULL) {
        // TODO : get event numbers ...
        pGame->events.padEvt(1, 1, pGame->pData);
    }
    if(pGame->events.mouseEvt != NULL) {
        // TODO : get event numbers ...
        pGame->events.mouseEvt(2, 2, pGame->pData);
    }

}
