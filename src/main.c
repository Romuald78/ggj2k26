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
#include "mod_cut.h"
#include "mod_paint.h"
#include "mod_junction.h"
#include "mod_power_supply.h"
#include "mod_garbage.h"
#include "mod_loader.h"
#include "mod_push.h"
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
    ud.modules = addGarbageModule(ud.modules, "GARBAGE", 40, 4);
    ud.actions = addAction(ud.actions, "TRASH" , ud.modules);



    // ========== LOADERS ==========
    ud.modules = addLoaderModule(ud.modules, "LOADER#1", 4, 10, MOD_RIGHT, MOD_BASE_1);
    ud.actions = addAction(ud.actions, "INCSPD1" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD1", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE1", ud.modules);
    ud.modules = addConveyModule  (ud.modules, "CONV#1", 7, 11, 20, MOD_RIGHT, SPEED_NOM*(rand()%21+90)/100.0);
    ud.actions = addAction(ud.actions, "PWRON1" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF1" , ud.modules);

    ud.modules = addLoaderModule(ud.modules, "LOADER#2", 4, 20, MOD_RIGHT, MOD_BASE_1);
    ud.actions = addAction(ud.actions, "INCSPD2" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD2", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE2", ud.modules);
    ud.modules = addConveyModule  (ud.modules, "CONV#2", 7, 21, 20, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON1" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF1" , ud.modules);

    ud.modules = addLoaderModule(ud.modules, "LOADER#3", 61, 4, MOD_DOWN, MOD_BASE_2);
    ud.actions = addAction(ud.actions, "INCSPD3" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD3", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE3", ud.modules);
    ud.modules = addConveyModule  (ud.modules, "CONV#3", 62, 7, 3, MOD_DOWN, SPEED_NOM*(rand()%21+90)/100.0);
    ud.actions = addAction(ud.actions, "PWRON3" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF3" , ud.modules);

    ud.modules = addLoaderModule(ud.modules, "LOADER#4", 71, 4, MOD_DOWN, MOD_BASE_2);
    ud.actions = addAction(ud.actions, "INCSPD4" , ud.modules);
    ud.actions = addAction(ud.actions, "DECSPD4", ud.modules);
    ud.actions = addAction(ud.actions, "TOGGLE4", ud.modules);
    ud.modules = addConveyModule  (ud.modules, "CONV#4", 72, 7, 3, MOD_DOWN, SPEED_NOM*(rand()%21+90)/100.0);
    ud.actions = addAction(ud.actions, "PWRON3" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF3" , ud.modules);

    // ========== CUT ==============
    ud.modules = addConveyModule  (ud.modules, "CONV#CUT1", 52, 13, 7, MOD_DOWN, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON4" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF4" , ud.modules);
    ud.modules = addJunctionModule(ud.modules, "JUNC#CUT", 52, 21, MOD_RIGHT, SPEED_NOM);
    ud.modules = addConveyModule  (ud.modules, "CONV#CUT2", 54, 21, 6, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON4" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF4" , ud.modules);

    ud.modules = addCutterModule(ud.modules, "CUT#1", 60, 19, SPEED_NOM);
    ud.actions = addAction(ud.actions, "CUTONE" , ud.modules);
    ud.actions = addAction(ud.actions, "CUTTWO" , ud.modules);

    ud.modules = addConveyModule  (ud.modules, "CONV#CUT3", 65, 21, 6, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON4" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF4" , ud.modules);

    // =========== PAINT ============


    // ======== NETWORKS ==========
    ud.modules = addJunctionModule(ud.modules, "JUNC#1IA", 28, 11, MOD_RIGHT, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#A", 30, 11, 10, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    // todo pusher CUT top to split B1/B2

    ud.modules = addConveyModule  (ud.modules, "CONV#B1", 43, 11, 8, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#3AB", 62, 11, MOD_RIGHT, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#B2", 54, 11, 7, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addConveyModule  (ud.modules, "CONV#B3", 64, 11, 7, MOD_RIGHT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#B4C", 72, 11, MOD_DOWN, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#C", 72, 13, 7, MOD_DOWN, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#CD", 72, 21, MOD_DOWN, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#D", 72, 23, 11, MOD_DOWN, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#DE", 72, 35, MOD_LEFT, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#E", 60, 35, 11, MOD_LEFT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#EF", 58, 35, MOD_LEFT, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#F", 48, 35, 9, MOD_LEFT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    // todo ADD PUSH TOP TO PAINT

    ud.modules = addConveyModule  (ud.modules, "CONV#PAINT1", 46, 23, 11, MOD_UP, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON4" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF4" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#PAINT", 46, 21, MOD_LEFT, SPEED_NOM);



    ud.modules = addConveyModule  (ud.modules, "CONV#G", 30, 35, 15, MOD_LEFT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);


    ud.modules = addConveyModule  (ud.modules, "CONV#PAINTout", 30, 21, 5, MOD_LEFT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON4" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF4" , ud.modules);
    ud.modules = addConveyModule  (ud.modules, "CONV#PAINTin", 40, 21, 5, MOD_LEFT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON4" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF4" , ud.modules);

    ud.modules = addPainterModule(ud.modules, "PAINT#1", 35, 19, SPEED_NOM);

    ud.modules = addJunctionModule(ud.modules, "JUNC#GH", 28, 35, MOD_UP, SPEED_NOM);

    ud.modules = addConveyModule  (ud.modules, "CONV#H1", 28, 23, 4, MOD_UP, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addConveyModule  (ud.modules, "CONV#H2", 28, 30, 4, MOD_UP, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addJunctionModule(ud.modules, "JUNC#2HI", 28, 21, MOD_UP, SPEED_NOM/1.5);

    ud.modules = addConveyModule  (ud.modules, "CONV#I", 28, 13, 7, MOD_UP, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);

    ud.modules = addPushModule  (ud.modules, "PUSH#garbage", 40, 10, MOD_UP, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PUSH0" , ud.modules);

    ud.modules = addPushModule  (ud.modules, "PUSH#cut", 51, 10, MOD_DOWN, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PUSH1" , ud.modules);

    ud.modules = addPushModule  (ud.modules, "PUSH#deliv", 27, 27, MOD_LEFT, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PUSH3" , ud.modules);

    ud.modules = addPushModule  (ud.modules, "PUSH#paint", 45, 34, MOD_UP, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PUSH2" , ud.modules);

    ud.modules = addConveyModule  (ud.modules, "CONV#H2", 41, 7, 3, MOD_UP, SPEED_NOM);
    ud.actions = addAction(ud.actions, "PWRON2" , ud.modules);
    ud.actions = addAction(ud.actions, "PWROFF2" , ud.modules);



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

