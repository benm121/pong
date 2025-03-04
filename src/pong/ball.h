#pragma once
#include "global.h"
#include "object.h"
#include "utils/log.h"

class Ball : public Object {
public:
    Ball()
    : Object(
        CENTER_POS,
        {0.0f, 255.0f, 150.0f},
        {15.0f, 15.0f},
        {0.0f, 0.0f},
        DEFAULT_SPEED
    ) {
        reset();
        LOG_INFO("vel: (%.3f, %.3f)", velocity_.x, velocity_.y);
    }

    void update(float dt);
    void reset(void);

    void flipVelX(bool randomize = true);
    void flipVelY(bool randomize = true);

public:
    float opacity_ = 0.0f;

private:
    void updateReset(float dt);
    void handleEdgeCollisions(void);
    void clampVelocity(void);

private:
    static constexpr float MIN_VELOCITY = 0.5f;
    static constexpr float MAX_VELOCITY = 3.0f;
    static constexpr float START_VELOCITY = 1.0f;
    static constexpr float DEFAULT_SPEED = 250.0f;
    static constexpr float DEFAULT_RESET_TIME = 1.0f;
    static constexpr float OFFSCREEN_DISTANCE = 100.0f; // how far the ball can go offscreen before being reset
    static constexpr glm::vec2 CENTER_POS = {global::SCREEN_WIDTH * 0.5f, global::SCREEN_HEIGHT * 0.5f};

    float resetTime_ = DEFAULT_RESET_TIME;
    bool beingReset_ = true;

};

