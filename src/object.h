#pragma once

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

struct Object {
    struct MoveState {
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
    };

    Object(
        const glm::vec2 &pos,
        const glm::vec3 &color,
        const glm::vec2 &size,
        const glm::vec2 &vel,
        float speed
    ) :
        position_(pos),
        color_(color),
        size_(size),
        speed_(speed)
    {}

    glm::vec2 position_;
    glm::vec3 color_;
    glm::vec2 size_;
    glm::vec2 velocity_;
    float speed_;
    MoveState moveState_;
};

