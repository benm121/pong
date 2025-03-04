#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <optional>


class Window {
public:
    Window(const std::string &title, uint32_t w, uint32_t h);
    ~Window();

    static std::optional<std::unique_ptr<Window>> create(const std::string &title, uint32_t w, uint32_t h);

    void clear(void) const;
    void update(void);

    inline bool shouldClose(void) const { return glfwWindowShouldClose(window_); }
    inline void setShouldClose(bool shouldClose) { glfwSetWindowShouldClose(window_, shouldClose); }

    GLFWwindow *getGlfwWindow(void) const { return window_; }

    uint32_t getWidth(void) const { return width_; }
    uint32_t getHeight(void) const { return height_; }

    float getDeltaTime(void) const;

private:
    bool init(void);

private:
    std::string title_;
    uint32_t width_, height_;
    GLFWwindow *window_ = nullptr;

    mutable double lastFrameTime_;

};

