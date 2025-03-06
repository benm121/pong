#include "paddle.h"
#include "global.h"

#include <algorithm>


// ===== Paddle =====


void Paddle::update(float dt) {
    // calculate acceleration and velocity for smooth movement
    float accel = 0.0f;

    if (moveState_.up) accel += ACCEL_FACTOR;
    if (moveState_.down) accel -= ACCEL_FACTOR;

    velocity_.y += accel * dt;

    if (!moveState_.up && !moveState_.down) {
        if (velocity_.y > 0.0f) {
            velocity_.y = std::max(velocity_.y - DECEL_FACTOR * dt, 0.0f);
        } else if (velocity_.y < 0.0f) {
            velocity_.y = std::min(velocity_.y + DECEL_FACTOR * dt, 0.0f);
        }
    }

    velocity_.y = std::clamp(velocity_.y, -speed_, speed_);
    position_.y += velocity_.y * dt;

    handleEdgeCollisions();
}

void Paddle::handleEdgeCollisions(void) {
    const float halfHeight = size_.y * 0.5f;
    position_.y = std::clamp(position_.y, halfHeight, global::SCREEN_HEIGHT - halfHeight);
}


// ===== PlayerPaddle =====


void PlayerPaddle::input(const InputManager &inputManager) {
    if (playerNum_ == Num::ONE) {
        moveState_.up = inputManager.isKeyPressed(GLFW_KEY_W);
        moveState_.down = inputManager.isKeyPressed(GLFW_KEY_S);
    } else {
        moveState_.up = inputManager.isKeyPressed(GLFW_KEY_UP);
        moveState_.down = inputManager.isKeyPressed(GLFW_KEY_DOWN);
    }
}


// ===== AIPaddle =====


void AIPaddle::trackBall(const Ball &ball) {
    const float quarterHeight = size_.y * 0.25f;

    if (ball.velocity_.x > 0.0f) {
        if (ball.position_.x > global::SCREEN_WIDTH * 0.5f) {
            moveState_.up = ball.position_.y > position_.y + quarterHeight;
            moveState_.down = ball.position_.y < position_.y - quarterHeight;
        }
    } else {
        moveState_.up = position_.y < global::SCREEN_HEIGHT * 0.5f - 100.0f;
        moveState_.down = position_.y > global::SCREEN_HEIGHT * 0.5f + 100.0f;
    }
}

