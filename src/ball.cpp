#include "ball.h"

#include <algorithm>


void Ball::update(float dt) {
    if (beingReset_) {
        updateReset(dt);
        return;
    }

    position_.x += speed_ * dt;

    handleEdgeCollisions();
}

void Ball::reset(void) {
    beingReset_ = true;
    opacity_ = 0.0f;
}

// returns true when reset time is finished
void Ball::updateReset(float dt) {
    position_ = CENTER_POS;
    resetTime_ -= dt;
    opacity_ = std::min(1.0f - resetTime_, 1.0f);

    if (resetTime_ <= 0.0f) {
        beingReset_ = false;
        resetTime_ = DEFAULT_RESET_TIME;
    }
}

void Ball::handleEdgeCollisions(void) {
    const float halfHeight = size_.y * 0.5f;
    position_.y = std::clamp(position_.y, halfHeight, global::SCREEN_HEIGHT - halfHeight);

    if (position_.x < -OFFSCREEN_DISTANCE ||
        position_.x > global::SCREEN_WIDTH + OFFSCREEN_DISTANCE) {
        reset();
    }
}

