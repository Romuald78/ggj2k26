#include "update.h"
#include "user_data.h"

int update(Game* pGame, float delta_sec){
    // check
    checkGame(pGame);
    
    return updateUser(pGame);
}
