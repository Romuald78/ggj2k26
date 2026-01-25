#include <unistd.h>
#include <fcntl.h>

#include "stddef.h"
#include "error.h"
#include "game.h"
#include "events.h"
#include "user_data.h"
#include "utils.h"

int main(){

    UserData ud;

    // Locals
    Game* pGame = createGame();
    setCallbacks(pGame, handleKeyEvt, handlePadEvt, handleMouseEvt);
    setData(pGame, &ud);
    initUser(pGame->pData);

    int flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    //disable_echo();
    // enable_raw_mode();
    gameLoop(pGame);
    // disable_raw_mode();
    //enable_echo();

    return 0;
}

