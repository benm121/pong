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
    };

    Game(const std::string &title, uint32_t width, uint32_t height)
        : title_(title),
        screenWidth_(width),
        screenHeight_(height)
    {}
    ~Game() = default;

    bool init(void);
    void start(Mode mode);

private:
    void handleCollisions(void);
    void submitCenterLines(size_t lineCount, float lineWidth, float lineHeight, float opacity);

private:
    uint32_t screenWidth_, screenHeight_;
    std::string title_;
    std::pair<float, float> scores_ = {0.0f, 0.0f}; // TODO: add scores with imgui
    uint32_t highScore_ = 0; // TODO: add ability to save and read high score

    std::unique_ptr<Window> window_;
    std::unique_ptr<InputManager> inputManager_;

    std::unique_ptr<Renderer> renderer_;
    std::shared_ptr<Shader> shader_;

    std::unique_ptr<PlayerPaddle> player1_;
    std::unique_ptr<PlayerPaddle> player2_;
    std::unique_ptr<Ball> ball_;

};

