#pragma once

#include "global.h"
#include "input.h"
#include "object.h"
#include "utils/log.h"


class Paddle : public Object {
public:
    Paddle(const glm::vec2 &pos)
    : Object{
        pos,
        {255.0f, 255.0f, 255.0f},
        {10.0f, 75.0f},
        {0.0f, 0.0f},
        DEFAULT_SPEED,
    },
    initialPos_(pos)
    {}
    ~Paddle() = default;

    void update(float dt);
    void resetPos(void) { position_ = initialPos_; }

public:
    static constexpr float DEFAULT_SPEED = 600.0f;
    static constexpr float DISTANCE_FROM_EDGE = 50.0f;
    static constexpr float ACCEL_FACTOR = 5000.0f;
    static constexpr float DECEL_FACTOR = 1800.0f;

private:
    void handleEdgeCollisions(void);

protected:
    glm::vec2 initialPos_;

};


class PlayerPaddle : public Paddle {
public:
    // determines player 1 or player 2
    enum class Num {
        ONE,
        TWO,
    };

    PlayerPaddle(Num num)
    : playerNum_(num), Paddle({0.0f, global::SCREEN_HEIGHT * 0.5f}) {
        if (playerNum_ == Num::ONE) {
            position_.x = DISTANCE_FROM_EDGE;
        } else {
            position_.x = global::SCREEN_WIDTH - DISTANCE_FROM_EDGE;
        }
        initialPos_.x = position_.x;
    }

    void input(const InputManager &inputManager);

private:
    Num playerNum_;

};

