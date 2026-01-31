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
#include "mod_garbage.h"
#include "mod_loader.h"

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


    // ========== POWER SUPPLIES ==========
    ud.modules = addPowerSupModule(ud.modules, "PWR#1", 1, 4, 4);
    ud.actions = addAction(ud.actions, "PWRON1" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF1", ud.modules);

    ud.modules = addPowerSupModule(ud.modules, "PWR#2", 2, 9, 4);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2", ud.modules);

    ud.modules = addPowerSupModule(ud.modules, "PWR#3", 3, 14, 4);
    ud.actions = addAction(ud.actions, "PWRON3" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF3", ud.modules);

    ud.modules = addPowerSupModule(ud.modules, "PWR#4", 4, 19, 4);
    ud.actions = addAction(ud.actions, "PWRON4" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF4", ud.modules);

    // ========== LOADING + GARBAGE ==========
    ud.modules = addGarbageModule(ud.modules, "PWR#4", 19, 34);



    // ========== LOADERS ==========
    ud.modules = addLoaderModule(ud.modules, "LOADER#1", 4, 12, MOD_RIGHT, MOD_BASE_1);
    ud.actions = addAction(ud.actions, "INCSPD1" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD1", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE1", ud.modules);

    ud.modules = addLoaderModule(ud.modules, "LOADER#2", 4, 22, MOD_RIGHT, MOD_BASE_1);
    ud.actions = addAction(ud.actions, "INCSPD2" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD2", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE2", ud.modules);

    ud.modules = addLoaderModule(ud.modules, "LOADER#3", 40, 4, MOD_DOWN, MOD_BASE_2);
    ud.actions = addAction(ud.actions, "INCSPD3" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD3", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE3", ud.modules);

    ud.modules = addLoaderModule(ud.modules, "LOADER#4", 60, 4, MOD_DOWN, MOD_BASE_2);
    ud.actions = addAction(ud.actions, "INCSPD4" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD4", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE4", ud.modules);

    // ========== CUT ==============


    // =========== PAINT ============


    // ======== NETWORKS ==========
    ud.modules = addConveyModule  (ud.modules, "CONV#1", 7, 13, 20, MOD_RIGHT, 0.050);
    ud.actions = addAction(ud.actions, "START1" , ud.modules);
    ud.actions = addAction(ud.actions, "STOP1" , ud.modules);

    ud.modules = addConveyModule  (ud.modules, "CONV#2", 7, 23, 20, MOD_RIGHT, 0.333);
    ud.actions = addAction(ud.actions, "START2" , ud.modules);
    ud.actions = addAction(ud.actions, "STOP2" , ud.modules);


    /*
    ud.modules = addJunctionModule(ud.modules, "JUNC#1", 20, 6, MOD_RIGHT, 0.25);
    ud.actions = addAction(ud.actions, "TURNL1", ud.modules);
    ud.actions = addAction(ud.actions, "TURNR1", ud.modules);

    ud.modules = addConveyModule  (ud.modules, "CONV#1H", 22, 6, 20, MOD_RIGHT, 0.25);
    ud.actions = addAction(ud.actions, "START1", ud.modules);
    ud.actions = addAction(ud.actions, "STOP1" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#2", 43, 6, MOD_RIGHT, 0.25);
    ud.actions = addAction(ud.actions, "TURNL2", ud.modules);
    ud.actions = addAction(ud.actions, "TURNR2", ud.modules);

*/

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

