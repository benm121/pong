#include "ball.h"
#include "utils/log.h"
#include "utils/random.h"

#include <glm/geometric.hpp>
#include <algorithm>


void Ball::update(float dt) {
    if (beingReset_) {
        updateReset(dt);
        return;
    }

    position_ += velocity_ * speed_ * dt;
    /*LOG_INFO("vel: (%.3f, %.3f)", velocity_.x, velocity_.y);*/

    handleEdgeCollisions();
    clampVelocity();
}

void Ball::reset(void) {
    beingReset_ = true;
    opacity_ = 0.0f;
    velocity_.x = rnd::flipCoin() ? -START_VELOCITY : START_VELOCITY;
    velocity_.y = 0.0f;
}

void Ball::horizCollision(bool randomizeVel) {
    if (randomizeVel) {
        velocity_.x *= -rnd::randFloat(0.9f, 1.2f);
    } else {
        velocity_.x *= -1.0f;
    }
}

void Ball::vertCollision(bool randomizeVel) {
    if (randomizeVel) {
        velocity_.y *= -rnd::randFloat(0.9f, 1.2f);
    } else {
        velocity_.y *= -1.0f;
    }
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
    const float halfSize = size_.y * 0.5f;
    position_.y = std::clamp(position_.y, halfSize, global::SCREEN_HEIGHT - halfSize);

    if (position_.x < -OFFSCREEN_DISTANCE ||
        position_.x > global::SCREEN_WIDTH + OFFSCREEN_DISTANCE) {
        reset();
    }

    if (position_.y - halfSize <= 0.0f || position_.y + halfSize >= global::SCREEN_HEIGHT) {
        vertCollision(false);
    }
}

void Ball::clampVelocity(void) {
    velocity_ = glm::normalize(velocity_) * std::clamp(
        glm::length(velocity_),
        MIN_VELOCITY,
        MAX_VELOCITY
    );
}

