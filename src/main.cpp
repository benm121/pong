#include "game.h"
#include "global.h"
#include "utils/log.h"

int main(void) {

    Game game("Pong", global::SCREEN_WIDTH, global::SCREEN_HEIGHT);

    if (!game.init()) {
        LOG_ERROR_RETURN(1, "failed to initialize game");
    }

    game.start(Game::Mode::MULTIPLAYER);

    return 0;
}

