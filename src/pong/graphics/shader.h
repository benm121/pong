#pragma once

#include "glad/glad.h"
#include "../utils/fileutils.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <string_view>
#include <unordered_map>


class Shader {
public:

    Shader(std::string_view vertPath, std::string_view fragPath);
    ~Shader();

    void activate(void) const;
    void deactivate(void);
    GLuint getID(void) const;

    void setUniform1i(const GLchar *name, GLint value) const;
    void setUniform1f(const GLchar *name, GLfloat value) const;
    void setUniform2f(const GLchar *name, GLfloat value1, GLfloat value2) const;
    void setUniform2f(const GLchar *name, const glm::vec2 &values) const;
    void setUniform3f(const GLchar *name, GLfloat value1, GLfloat value2, GLfloat value3) const;
    void setUniform3f(const GLchar *name, const glm::vec3 &values) const;
    void setUniform4f(const GLchar *name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4) const;
    void setUniform4f(const GLchar *name, const glm::vec4 &values) const;
    void setUniformMat4f(const GLchar *name, const glm::mat4 &data) const;

private:
    GLuint createShader(std::string_view path, GLenum type) const;
    void checkCompileErrors(GLuint shader, std::string_view type) const;
    void checkLinkErrors() const;
    GLint getUniformLocation(const GLchar *name) const;

private:
    GLuint id_ = 0;
    // mutable to allow changes to cache from const const methods
    mutable std::unordered_map<std::string, GLint> uniformCache_;
};



