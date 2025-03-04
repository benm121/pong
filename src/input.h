#pragma once

#include "window.h"

class InputManager {
public:
    InputManager(GLFWwindow *window) : window_(window) {
        init();
    }
    ~InputManager() = default;

    void keyCallbackImpl(GLFWwindow *window, int key, int scancode, int action, int mods);
    bool isKeyPressed(uint32_t keycode) const;

private:
    void init(void);

private:
    static constexpr uint16_t MAX_KEYS = 1024;
    bool keys_[MAX_KEYS];

    GLFWwindow *window_ = nullptr; // for input related functions

};

