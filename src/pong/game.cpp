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

        handleCollisions();

        submitCenterLines(20, 3.0f, 15.0f, 0.5f);

        renderer_->submit(*player1_);
        renderer_->submit(*player2_);
        renderer_->submit(*ball_, ball_->opacity_);

        renderer_->flush();

        window_->update();
    }
}

void Game::handleCollisions(void) {
    auto handlePaddleCollision = [this](Paddle &paddle) {
        if (!collision::AABB(paddle, *ball_)) return;

        // half dimensions
        float halfBallWidth = ball_->size_.x * 0.5f;
        float halfBallHeight = ball_->size_.y * 0.5f;
        float halfPaddleWidth = paddle.size_.x * 0.5f;
        float halfPaddleHeight = paddle.size_.y * 0.5f;

        // paddle edges
        float paddleLeft = paddle.position_.x - halfPaddleWidth;
        float paddleRight = paddle.position_.x + halfPaddleWidth;
        float paddleTop = paddle.position_.y + halfPaddleHeight;
        float paddleBottom = paddle.position_.y - halfPaddleHeight;

        // ball edges
        float ballLeft = ball_->position_.x - halfBallWidth;
        float ballRight = ball_->position_.x + halfBallWidth;
        float ballTop = ball_->position_.y + halfBallHeight;
        float ballBottom = ball_->position_.y - halfBallHeight;

        // collision side
        bool isLeftCollision = ballRight > paddleLeft && ballLeft < paddleLeft;
        bool isRightCollision = ballLeft < paddleRight && ballRight > paddleRight;
        bool isTopCollision = ballBottom > paddleTop && ballTop < paddleTop;
        bool isBottomCollision = ballTop < paddleBottom && ballBottom > paddleBottom;

        // prioritize horizontal over vertical
        if (isLeftCollision || isRightCollision) {
            ball_->horizCollision();

            if (isLeftCollision) { // fix clipping
                ball_->position_.x = paddleLeft - halfBallWidth - 0.1f;
            } else {
                ball_->position_.x = paddleRight + halfBallWidth + 0.1f;
            }
        } else if (isTopCollision || isBottomCollision) {
            ball_->vertCollision();

            if (isTopCollision) { // fix clipping
                ball_->position_.y = paddleTop + halfBallHeight + 0.1f;
            } else {
                ball_->position_.y = paddleBottom - halfBallHeight - 0.1f;
            }
        }
    };

    handlePaddleCollision(*player1_);
    handlePaddleCollision(*player2_);
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

