#include "input.h"
#include "utils/log.h"


static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    InputManager *input = (InputManager *)glfwGetWindowUserPointer(window);
    if (input) {
        input->keyCallbackImpl(window, key, scancode, action, mods);
    }
}

// callback implementations in class
void InputManager::keyCallbackImpl(GLFWwindow *window, int key, int scancode, int action, int mods) {
    keys_[key] = action != GLFW_RELEASE;
    /*if (action != GLFW_RELEASE) LOG_INFO("key pressed: %d", key);*/
}


void InputManager::init(void) {
    glfwSetWindowUserPointer(window_, this);
    glfwSetKeyCallback(window_, keyCallback);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    for (int i = 0; i < MAX_KEYS; ++i) {
        keys_[i] = false;
    }
}


bool InputManager::isKeyPressed(uint32_t keycode) const {
    if (keycode >= MAX_KEYS) {
        LOG_ERROR("key %d exceeds max keys", keycode);
        return false;
    }
    return keys_[keycode];
}

