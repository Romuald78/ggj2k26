#include <unistd.h>
#include <fcntl.h>

#include "stddef.h"
#include "error.h"
#include "game.h"
#include "events.h"
#include "user_data.h"
#include "utils.h"
#include "module.h"
#include "mod_convey.h"

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
    ud.modules = addConveyModule(ud.modules, "LINE#1H", 11, 5, 20, MOD_RIGHT, 20);
    ud.modules = addConveyModule(ud.modules, "LINE#2V", 31, 6, 10, MOD_DOWN, 15);
    ud.modules = addConveyModule(ud.modules, "LINE#3H", 11, 16, 20, MOD_LEFT, 10);
    ud.modules = addConveyModule(ud.modules, "LINE#4V", 10, 6, 10, MOD_UP, 5);


    // init Fill modules
    // TODO


    //disable_echo();
    // enable_raw_mode();
    gameLoop(pGame);
    // disable_raw_mode();
    //enable_echo();

    return 0;
}

