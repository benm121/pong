#include "shader.h"

#include "../utils/log.h"


Shader::Shader(std::string_view vertPath, std::string_view fragPath) {
        id_ = glCreateProgram();
        GLuint vert = createShader(vertPath, GL_VERTEX_SHADER);
        GLuint frag = createShader(fragPath, GL_FRAGMENT_SHADER);
        glAttachShader(id_, vert);
        glAttachShader(id_, frag);
        glLinkProgram(id_);
        glDeleteShader(vert);
        glDeleteShader(frag);
}

Shader::~Shader() {
    if (id_ != 0) glDeleteProgram(id_);
}

void Shader::activate(void) const { glUseProgram(id_); }

void Shader::deactivate(void) { glUseProgram(0); }

GLuint Shader::getID(void) const { return id_; }

void Shader::setUniform1i(const GLchar *name, GLint value) const {
    activate();
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const GLchar *name, GLfloat value) const {
    activate();
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform2f(const GLchar *name, GLfloat value1, GLfloat value2) const {
    activate();
    glUniform2f(getUniformLocation(name), value1, value2);
}

void Shader::setUniform2f(const GLchar *name, const glm::vec2 &values) const {
    activate();
    glUniform2f(getUniformLocation(name), values.r, values.g);
}

void Shader::setUniform3f(const GLchar *name, GLfloat value1, GLfloat value2, GLfloat value3) const {
    activate();
    glUniform3f(getUniformLocation(name), value1, value2, value3);
}

void Shader::setUniform3f(const GLchar *name, const glm::vec3 &values) const {
    activate();
    glUniform3f(getUniformLocation(name), values.r, values.g, values.b);
}

void Shader::setUniform4f(const GLchar *name, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4) const {
    activate();
    glUniform4f(getUniformLocation(name), value1, value2, value3, value4);
}

void Shader::setUniform4f(const GLchar *name, const glm::vec4 &values) const {
    activate();
    glUniform4f(getUniformLocation(name), values.r, values.g, values.b, values.a);
}

void Shader::setUniformMat4f(const GLchar *name, const glm::mat4 &data) const {
    activate();
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &data[0][0]);
}

GLuint Shader::createShader(std::string_view path, GLenum type) const {
    GLuint shader = glCreateShader(type);
    std::string src = fileutils::readToString(path).value_or("");
    const char *shaderSrc = src.c_str();

    glShaderSource(shader, 1, &shaderSrc, 0);
    glCompileShader(shader);
    checkCompileErrors(shader, (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));

    return shader;
}

void Shader::checkCompileErrors(GLuint shader, std::string_view type) const {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        LOG_ERROR("failed to compile %s shader: %s", type.data(), infoLog);
    }
}

void Shader::checkLinkErrors(void) const {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 1024, nullptr, infoLog);
        LOG_ERROR("failed to link program: %s", infoLog);
    }
}

GLint Shader::getUniformLocation(const GLchar *name) const {
    // check if uniform location is already in cache
    auto it = uniformCache_.find(name);
    if (it != uniformCache_.end()) {
        return it->second;
    }

    // if not, get from opengl and add to cache
    GLint location = glGetUniformLocation(id_, name);
    if (location == -1) {
        LOG_ERROR("uniform %s not found in shader program", name);
    }

    uniformCache_[name] = location;
    return location;
}


