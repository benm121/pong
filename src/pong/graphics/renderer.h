#pragma once

#include "../object.h"
#include "quad.h"
#include "shader.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

#include <memory>
#include <queue>

class Renderer {
public:
    struct RenderData {
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;
        float opacity = 1.0f;
    };

    Renderer() = default;
    ~Renderer() = default;

    void submit(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec3 &color, float opacity = 1.0f);
    void submit(const Object &obj, float opacity = 1.0f);
    void flush(void);

    void setShader(Shader *shader) { shader_ = shader; }
    void setProjection(const glm::mat4 &proj) { proj_ = proj; }

private:
    glm::mat4 createModel(const glm::vec2 &position, const glm::vec2 &size);

private:
    std::queue<RenderData> renderQueue_;
    Shader *shader_;
    glm::mat4 proj_{1.0f};

    const Quad quad_;
};

