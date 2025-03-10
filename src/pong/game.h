#pragma once

#include "ball.h"
#include "input.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "paddle.h"
#include "window.h"

#include <memory>
#include <utility>

class Game {
public:
    enum class Mode {
        SINGLEPLAYER,
        MULTIPLAYER,
        MENU
    };
    // attributes that will change between games (first to 3)
    struct Current {
        std::pair<uint32_t, uint32_t> scores = {0, 0};
        bool started = false;
        bool ended = false;
    };

    Game(const std::string &title, uint32_t width, uint32_t height)
        : title_(title),
        screenWidth_(width),
        screenHeight_(height)
    {}
    ~Game();

    bool init(void);
    void start(void);
    void setModeMenu(void) { mode_ = Mode::MENU; }
    void setModeMultiplayer(void) { mode_ = Mode::MULTIPLAYER; }
    void setModeSingleplayer(void) { mode_ = Mode::SINGLEPLAYER; }

private:
    void startMenu(void);
    void startGame(void);

    void handleCollisions(void);
    void submitCenterLines(size_t lineCount, float lineWidth, float lineHeight, float opacity);
    void checkScoreConditions(float dt);

private:
    static constexpr float DEFAULT_START_DELAY = 2.0f; // small delay before starting game mode
    static constexpr uint32_t SCORE_TO_WIN = 3;

    std::string title_;
    uint32_t screenWidth_, screenHeight_;
    uint32_t gamesWon_ = 0;
    uint32_t highScore_ = 0; // TODO: add ability to save and read high score

    Mode mode_ = Mode::MENU;
    Current current_;
    float startDelay_ = DEFAULT_START_DELAY;

    std::unique_ptr<Window> window_;
    std::unique_ptr<InputManager> inputManager_;

    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<Shader> shader_;

    std::unique_ptr<PlayerPaddle> player1_;
    std::unique_ptr<PlayerPaddle> player2_;
    std::unique_ptr<AIPaddle> ai_;
    std::unique_ptr<Ball> ball_;

};

