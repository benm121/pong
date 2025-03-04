#pragma once

#include <array>
#include <cstddef>

#include <glad/glad.h>

class Quad {
public:
    Quad();
    ~Quad();

    void bind(void) const { glBindVertexArray(vao_); }
    void unbind(void) const { glBindVertexArray(0); }

    size_t indexCount(void) const { return INDICES.size(); }

private:
    uint32_t vao_ = 0;
    uint32_t vbo_ = 0;
    uint32_t ebo_ = 0;

    static constexpr std::array<float, 12> VERTICES {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    static constexpr std::array<uint32_t, 6> INDICES {
        0, 1, 2, 2, 3, 0
    };

};

