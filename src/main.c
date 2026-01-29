#include <unistd.h>
#include <fcntl.h>

#include "draw.h"
#include "stddef.h"
#include "error.h"
#include "game.h"
#include "product.h"
#include "events.h"
#include "user_data.h"
#include "utils.h"
#include "module.h"
#include "mod_convey.h"
#include "mod_junction.h"

int main(int argc, char** argv){

    UserData ud;

    // Locals
    Game* pGame = createGame();
    setCallbacks(pGame, handleKeyEvt, handlePadEvt, handleMouseEvt);
    setData(pGame, &ud);
    initUser(pGame->pData);

    int flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    // ============================================
    // Create Products (?)
    // ============================================
    ud.products = addProduct(ud.products, "📦", 20, 19);


    // ============================================
    // Create modules + Add actions
    // ============================================
    ud.modules = addJunctionModule(ud.modules, "JUNC#41", 10, 6, MOD_RIGHT, 0.25);

    ud.modules = addConveyModule  (ud.modules, "CONV#1H", 12, 6, 20, MOD_RIGHT, 0.5);
    ud.actions = addAction(ud.actions, "START", ud.modules);
    ud.actions = addAction(ud.actions, "STOP", ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#12", 33, 6, MOD_DOWN, 0.25);

    ud.modules = addConveyModule  (ud.modules, "CONV#2V", 33, 8, 10, MOD_DOWN, 0.25);
    ud.actions = addAction(ud.actions, "START", ud.modules);
    ud.actions = addAction(ud.actions, "STOP", ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#23", 33, 19, MOD_LEFT, 0.25);

    ud.modules = addConveyModule  (ud.modules, "CONV#3H", 12, 19, 20, MOD_LEFT, 0.125);
    ud.actions = addAction(ud.actions, "START", ud.modules);
    ud.actions = addAction(ud.actions, "STOP", ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#34", 10, 19, MOD_UP, 0.25);

    ud.modules = addConveyModule  (ud.modules, "CONV#4V", 10, 8, 10, MOD_UP, 0.0625);
    ud.actions = addAction(ud.actions, "START", ud.modules);
    ud.actions = addAction(ud.actions, "STOP", ud.modules);




    // INTRO + SPLASH SCREENS
    /*
    displayAscii("./assets/ggj.ascii", "Global Game Jam 2026 - CERGY - FRANCE", 8000, 44, 1);
    displayAscii("./assets/rph.ascii", "       RPH STUDIO presents...", 10000, 40, 2);
    displayAscii("./assets/amazin.ascii", "OPTICAL READERS MATTER", 15000, 15, 3);
    //*/

    //disable_echo();
    // enable_raw_mode();
    gameLoop(pGame);
    // disable_raw_mode();
    //enable_echo();

    return 0;
}

