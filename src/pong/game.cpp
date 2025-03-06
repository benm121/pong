#include "game.h"
#include "paddle.h"
#include "ui.h"
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
    ai_ = std::make_unique<AIPaddle>();

    ball_ = std::make_unique<Ball>();

    return true;
}

void Game::start(void) {
    while (!window_->shouldClose()) {
        window_->clear();

        if (mode_ == Mode::MENU) {
            startMenu();
        } else {
            startGame();
        }

        window_->update();
    }
}

void Game::startMenu(void) {
    // functions to call when game mode is selected
    static auto spFunc = [this](void) { setModeSingleplayer(); };
    static auto mpFunc = [this](void) { setModeMultiplayer(); };
    static auto quitFunc = [this](void) { window_->setShouldClose(true); };

    ui::drawMenu(spFunc, mpFunc, quitFunc);
    startDelay_ = DEFAULT_START_DELAY;
}

void Game::startGame(void) {
    if (inputManager_->isKeyPressed(GLFW_KEY_ESCAPE)) {
        setModeMenu();
        ball_->reset();
        player1_->resetPos();
        player2_->resetPos();
        scores_ = {0, 0};
        startDelay_ = DEFAULT_START_DELAY;
        return;
    }

    float dt = window_->getDeltaTime();
    bool multiplayer = mode_ == Mode::MULTIPLAYER;
    startDelay_ -= 0.1f; // using dt creates issues when idling in the menu

    if (startDelay_ <= 0.0f) {
        player1_->input(*inputManager_);
        if (multiplayer) {
            player2_->input(*inputManager_);
        } else {
            ai_->trackBall(*ball_);
        }

        player1_->update(dt);
        if (multiplayer) {
            player2_->update(dt);
        } else {
            ai_->update(dt);
        }
        ball_->update(dt);

        handleCollisions();
        checkScoreConditions(dt);
        submitCenterLines(20, 3.0f, 15.0f, 0.5f);
    }

    renderer_->submit(*player1_);
    if (multiplayer) {
        renderer_->submit(*player2_);
    } else {
        renderer_->submit(*ai_);
    }
    renderer_->submit(*ball_, ball_->opacity_);

    renderer_->flush();

    ui::drawScore(scores_.first, 10, 10);
    ui::drawScore(scores_.second, global::SCREEN_WIDTH - 110, 10);
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

        // adjust y velocity based on point of contact with paddle
        float paddleCenterY = paddle.position_.y;
        float contactY = ball_->position_.y - paddleCenterY;
        float normalizedContact = contactY / halfPaddleHeight;
        float maxBounceAngle = glm::radians(90.0f);
        float newVelY = std::sinf(maxBounceAngle * normalizedContact);

        ball_->velocity_.y = newVelY;
    };

    handlePaddleCollision(*player1_);
    if (mode_ == Mode::MULTIPLAYER) {
        handlePaddleCollision(*player2_);
    } else {
        handlePaddleCollision(*ai_);
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

void Game::checkScoreConditions(float dt) {
    static float cooldown = 1.0f;
    cooldown -= dt;
    if (cooldown > 0.0f) return;

    if (ball_->position_.x < 0.0f) {
        ++scores_.second;
        cooldown = 1.0f;
        return;
    } else if (ball_->position_.x > global::SCREEN_WIDTH) {
        ++scores_.first;
        cooldown = 1.0f;
        return;
    }
}

