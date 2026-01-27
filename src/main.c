#include <unistd.h>
#include <fcntl.h>

#include "draw.h"
#include "stddef.h"
#include "error.h"
#include "game.h"
#include "events.h"
#include "user_data.h"
#include "utils.h"
#include "module.h"
#include "mod_convey.h"
#include "mod_junction.h"

int main(){

    UserData ud;

    // Locals
    Game* pGame = createGame();
    setCallbacks(pGame, handleKeyEvt, handlePadEvt, handleMouseEvt);
    setData(pGame, &ud);
    initUser(pGame->pData);

    int flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    // Create modules
    ud.modules = addJunctionModule(ud.modules, "J#41", 10, 5, MOD_RIGHT);
    ud.modules = addConveyModule  (ud.modules, "LINE#1H", 11, 5, 20, MOD_RIGHT, 20);
    conveyActions(ud.modules, "START");

    ud.modules = addJunctionModule(ud.modules, "J#12", 31, 5, MOD_DOWN);
    ud.modules = addConveyModule  (ud.modules, "LINE#2V", 31, 6, 10, MOD_DOWN, 15);
    conveyActions(ud.modules, "START");

    ud.modules = addJunctionModule(ud.modules, "J#23", 31, 16, MOD_LEFT);
    ud.modules = addConveyModule  (ud.modules, "LINE#3H", 11, 16, 20, MOD_LEFT, 10);
    conveyActions(ud.modules, "START");

    ud.modules = addJunctionModule(ud.modules, "J#34", 10, 16, MOD_UP);
    ud.modules = addConveyModule  (ud.modules, "LINE#4V", 10, 6, 10, MOD_UP, 5);
    conveyActions(ud.modules, "START");

    // INTRO + SPLASH SCREENS
    /*
    displayAscii("./assets/ggj.ascii", "Global Game Jam 2026 - Cergy - France", 8000, 43, 1);
    displayAscii("./assets/rph.ascii", "       RPH Studio presents...", 10000, 40, 2);
    displayAscii("./assets/amazin.ascii", "OPTICAL READERS MATTERS", 15000, 15, 3);
    //*/

    //disable_echo();
    // enable_raw_mode();
    gameLoop(pGame);
    // disable_raw_mode();
    //enable_echo();

    return 0;
}

