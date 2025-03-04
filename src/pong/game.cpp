#include "game.h"
#include "paddle.h"
#include "utils/collision.h"
#include "utils/log.h"

#include <glm/ext/matrix_clip_space.hpp>

#include <filesystem>

bool Game::init(void) {

    auto result = Window::create(title_, screenWidth_, screenHeight_);
    if (!result.has_value()) {
        LOG_ERROR_RETURN(false, "failed to create window");
    }
    window_ = std::move(result.value());

    inputManager_ = std::make_unique<InputManager>(window_->getGlfwWindow());

    shader_ = std::make_shared<Shader>(
        std::filesystem::absolute("assets/shaders/default_vert.glsl").c_str(),
        std::filesystem::absolute("assets/shaders/default_frag.glsl").c_str()
    );

    renderer_ = std::make_unique<Renderer>();
    renderer_->setShader(shader_);
    renderer_->setProjection(
        glm::ortho(
            0.0f, static_cast<float>(window_->getWidth()),
            0.0f, static_cast<float>(window_->getHeight()),
            -0.1f, 1.0f
        )
    );

    player1_ = std::make_unique<PlayerPaddle>(PlayerPaddle::Num::ONE);
    player2_ = std::make_unique<PlayerPaddle>(PlayerPaddle::Num::TWO);

    ball_ = std::make_unique<Ball>();

    return true;
}

void Game::start(Mode mode) {
    if (mode != Mode::MULTIPLAYER) return; // TODO: add single player mode later

    while (!window_->shouldClose() && !inputManager_->isKeyPressed(GLFW_KEY_ESCAPE)) {
        window_->clear();

        float dt = window_->getDeltaTime();

        player1_->input(*inputManager_);
        player2_->input(*inputManager_);

        player1_->update(dt);
        player2_->update(dt);
        ball_->update(dt);

        submitCenterLines(20, 3.0f, 15.0f, 0.5f);

        renderer_->submit(*player1_);
        renderer_->submit(*player2_);
        renderer_->submit(*ball_, ball_->opacity_);

        renderer_->flush();

        window_->update();
    }
}

void Game::submitCenterLines(size_t lineCount, float lineWidth, float lineHeight, float opacity) {
    static constexpr float centerX = global::SCREEN_WIDTH * 0.5f;

    for (size_t i = 0; i < lineCount; ++i) {
        const float spacing = (global::SCREEN_HEIGHT - (lineCount * lineHeight)) / (lineCount - 1);
        renderer_->submit(
            {centerX, (i * (lineHeight + spacing)) + lineHeight * 0.5f},
            {lineWidth, lineHeight},
            {255.0f, 255.0f, 255.0f},
            opacity
        );
    }
}

