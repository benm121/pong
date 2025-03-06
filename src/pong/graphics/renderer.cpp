#include "renderer.h"
#include "../utils/log.h"

#include <glad.h>

#include <glm/ext/matrix_transform.hpp>

void Renderer::submit(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec3 &color, float opacity) {
    renderQueue_.push({pos, size, color, opacity}); // using emplace here creates issues on mac for some reason
}

void Renderer::submit(const Object &obj, float opacity) {
    renderQueue_.push({obj.position_, obj.size_, obj.color_, opacity});
};

void Renderer::flush(void) {
    if (!shader_) {
        LOG_ERROR("no shader set in renderer");
        return;
    }
    if (proj_ == glm::mat4(1.0f)) {
        LOG_ERROR("no projection matrix set in renderer");
        return;
    }

    shader_->activate();
    shader_->setUniformMat4f("uProj", proj_);

    while (!renderQueue_.empty()) {
        auto data = renderQueue_.front();

        glm::mat4 model = createModel(data.position, data.size);

        shader_->setUniformMat4f("uModel", model);
        shader_->setUniform3f("uColor", data.color);
        shader_->setUniform1f("uOpacity", data.opacity);

        quad_.bind();
        glDrawElements(GL_TRIANGLES, quad_.indexCount(), GL_UNSIGNED_INT, nullptr);

        renderQueue_.pop();
    }
}

glm::mat4 Renderer::createModel(const glm::vec2 &position, const glm::vec2 &size) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, {position, 0.0f});
    model = glm::scale(model, {size, 1.0f});
    return model;
}

