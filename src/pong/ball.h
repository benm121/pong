#pragma once
#include "global.h"
#include "object.h"


class Ball : public Object {
public:
    Ball()
    : Object{
        CENTER_POS,             // position
        {1.0f, 1.0f, 1.0f},     // color
        {15.0f, 15.0f},         // size
        {0.0f, 0.0f},           // velocity
        DEFAULT_SPEED           // speed
    } {
        reset();
    }

    void update(float dt);
    void reset(void);

    void horizCollision(bool randomizeVel = true);
    void vertCollision(bool randomizeVel = true);

public:
    float opacity_ = 0.0f;

private:
    void updateReset(float dt);
    void handleEdgeCollisions(void);
    void clampVelocity(void);

private:
    static constexpr float MIN_VELOCITY = 1.0f;
    static constexpr float MAX_VELOCITY = 1.6f;
    static constexpr float START_VELOCITY = 1.0f;
    static constexpr float DEFAULT_SPEED = 600.0f;
    static constexpr float DEFAULT_RESET_TIME = 1.0f;
    static constexpr float OFFSCREEN_DISTANCE = 100.0f; // how far the ball can go offscreen before being reset
    static constexpr glm::vec2 CENTER_POS = {global::SCREEN_WIDTH * 0.5f, global::SCREEN_HEIGHT * 0.5f};

    float resetTime_ = DEFAULT_RESET_TIME;
    bool beingReset_ = true;
};

