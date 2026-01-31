#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

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
#include "parameters.h"

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
    ud.modules = addGarbageModule(ud.modules, "PWR#4", 19, 28);



    // ========== LOADERS ==========
    ud.modules = addLoaderModule(ud.modules, "LOADER#1", 4, 10, MOD_RIGHT, MOD_BASE_1);
    ud.actions = addAction(ud.actions, "INCSPD1" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD1", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE1", ud.modules);
    ud.modules = addConveyModule  (ud.modules, "CONV#1", 7, 11, 20, MOD_RIGHT, SPEED_NOM*(rand()%21+90)/100.0);
    ud.actions = addAction(ud.actions, "PWRON1" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF1" , ud.modules);

    ud.modules = addLoaderModule(ud.modules, "LOADER#2", 4, 24, MOD_RIGHT, MOD_BASE_1);
    ud.actions = addAction(ud.actions, "INCSPD2" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD2", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE2", ud.modules);
    ud.modules = addConveyModule  (ud.modules, "CONV#2", 7, 25, 20, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON1" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF1" , ud.modules);

    ud.modules = addLoaderModule(ud.modules, "LOADER#3", 40, 4, MOD_DOWN, MOD_BASE_2);
    ud.actions = addAction(ud.actions, "INCSPD3" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD3", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE3", ud.modules);

    ud.modules = addLoaderModule(ud.modules, "LOADER#4", 71, 4, MOD_DOWN, MOD_BASE_2);
    ud.actions = addAction(ud.actions, "INCSPD4" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD4", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE4", ud.modules);

    // ========== CUT ==============


    // =========== PAINT ============


    // ======== NETWORKS ==========
    ud.modules = addJunctionModule(ud.modules, "JUNC#1IA", 28, 11, MOD_RIGHT, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#A", 30, 11, 10, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#3AB", 41, 11, MOD_RIGHT, SPEED_NOM);

    // todo pusher CUT top to split B1/B2
    ud.modules = addConveyModule  (ud.modules, "CONV#B1", 43, 11, 13, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addConveyModule  (ud.modules, "CONV#B", 59, 11, 12, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#B4C", 72, 11, MOD_DOWN, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#C", 72, 13, 7, MOD_DOWN, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);


    ud.modules = addJunctionModule(ud.modules, "JUNC#CD", 72, 21, MOD_DOWN, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#D", 72, 23, 10, MOD_DOWN, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#DE", 72, 34, MOD_LEFT, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#E", 60, 34, 11, MOD_LEFT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#EF", 58, 34, MOD_LEFT, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#F", 47, 34, 10, MOD_LEFT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    // todo ADD PUSH TOP TO PAINT

    ud.modules = addConveyModule  (ud.modules, "CONV#G", 30, 34, 14, MOD_LEFT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#GH", 28, 34, MOD_UP, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#H", 28, 27, 6, MOD_UP, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#2HI", 28, 25, MOD_UP, SPEED_NOM/1.5);

    ud.modules = addConveyModule  (ud.modules, "CONV#I", 28, 13, 11, MOD_UP, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);


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

