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
#include "mod_power_supply.h"

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
    /*
    ud.products = addProduct(ud.products, "📦", 20, 19);
    //*/

    // ============================================
    // Create modules + Add actions
    // ============================================
    // commands for same types of modules shall contain letters followed by numbers
    // full command name will be compared to call the "module" action method for the correct module
    // Only text will be compared in the "module" action method in order to save some code !!

    ud.modules = addPowerSupModule(ud.modules, "PWR#1", 1, 10, 16);
    ud.actions = addAction(ud.actions, "PWRON1" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF1", ud.modules);

    ud.modules = addPowerSupModule(ud.modules, "PWR#2", 2, 15, 16);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2", ud.modules);



    ud.modules = addJunctionModule(ud.modules, "JUNC#1", 10, 6, MOD_RIGHT, 0.25);
    ud.actions = addAction(ud.actions, "TURNL1", ud.modules);
    ud.actions = addAction(ud.actions, "TURNR1", ud.modules);

    ud.modules = addConveyModule  (ud.modules, "CONV#1H", 12, 6, 20, MOD_RIGHT, 0.25);
    ud.actions = addAction(ud.actions, "START1", ud.modules);
    ud.actions = addAction(ud.actions, "STOP1" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#2", 33, 6, MOD_RIGHT, 0.25);
    ud.actions = addAction(ud.actions, "TURNL2", ud.modules);
    ud.actions = addAction(ud.actions, "TURNR2", ud.modules);



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

