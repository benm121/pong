#pragma once
#include "global.h"
#include "object.h"

class Ball : public Object {
public:
    Ball()
    : Object(
        CENTER_POS,
        {0.0f, 255.0f, 150.0f},
        {15.0f, 15.0f},
        {0.0f, 0.0f},
        DEFAULT_SPEED
    ) {}

    void update(float dt);
    void reset(void);

public:
    float opacity_ = 0.0f;

private:
    void updateReset(float dt);
    void handleEdgeCollisions(void);

private:
    static constexpr float DEFAULT_SPEED = 250.0f;
    static constexpr float DEFAULT_RESET_TIME = 1.0f;
    static constexpr float OFFSCREEN_DISTANCE = 100.0f; // how far the ball can go offscreen before being reset
    static constexpr glm::vec2 CENTER_POS = {global::SCREEN_WIDTH * 0.5f, global::SCREEN_HEIGHT * 0.5f};

    float resetTime_ = DEFAULT_RESET_TIME;
    bool beingReset_ = true;

};

