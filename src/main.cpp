#include "pong/game.h"
#include "pong/global.h"
#include "pong/utils/log.h"

std::filesystem::path global::execPath;

int main(int argc, char **argv) {
    if (argc < 1) {
        LOG_ERROR_RETURN(1, "no argument provided");
    }
    global::execPath = std::filesystem::canonical(argv[0]).parent_path().parent_path(); // one dir back from "build"

    Game game("Pong", global::SCREEN_WIDTH, global::SCREEN_HEIGHT);

    if (!game.init()) {
        LOG_ERROR_RETURN(1, "failed to initialize game");
    }

    game.start();

    return 0;
}

