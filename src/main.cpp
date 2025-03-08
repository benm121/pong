#include "pong/game.h"
#include "pong/global.h"
#include "pong/utils/log.h"


int main(void) {

    Game game("Pong", global::SCREEN_WIDTH, global::SCREEN_HEIGHT);

    if (!game.init()) {
        LOG_ERROR_RETURN(1, "failed to initialize game");
    }

    game.start();

    return 0;
}

