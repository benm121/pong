#include "window.h"
#include "utils/log.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <memory>


// callback functions

static void errorCallback(int code, const char *description) {
    LOG_ERROR("(GLFW - %d): %s", code, description);
}

static void GLAPIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
GLsizei length, const GLchar *message, const void *userParam) {
    LOG_ERROR("(GL DEBUG): %s", message);
}

Window::Window(const std::string& title, uint32_t w, uint32_t h)
: title_(title), width_(w), height_(h) {}

Window::~Window() {
    cleanImGui();

    glfwDestroyWindow(window_);
    glfwTerminate();
}

// returns either a new instance of Window in a unique_ptr or nullopt if failed to create
std::optional<std::unique_ptr<Window>> Window::create(const std::string& title, uint32_t w, uint32_t h) {
    auto window = std::make_unique<Window>(title, w, h);

    if (!window->init()) {
        return std::nullopt;
    }

    LOG_INFO("%s, Version %s", glGetString(GL_VENDOR), glGetString(GL_VERSION));
    return std::move(window);
}

bool Window::init(void) {
    // init glfw and create window
    if (!glfwInit()) {
        LOG_ERROR("failed to initialize glfw");
        return false;
    }
    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
    if (!window_) {
        LOG_ERROR("failed to create window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("failed to initialize glad");
        glfwDestroyWindow(window_);
        glfwTerminate();
        return false;
    }

    // additional settings
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugMessageCallback, nullptr);

    glEnable(GL_BLEND); // enable transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    lastFrameTime_ = glfwGetTime();

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    initImGui();

    return true;
}

void Window::clear(void) const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update(void) {
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

float Window::getDeltaTime(void) const {
    double currentFrameTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentFrameTime - lastFrameTime_);
    lastFrameTime_ = currentFrameTime;
    return deltaTime;
}

void Window::initImGui(void) const {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/PressStart2P-Regular.ttf", 20);
}

void Window::cleanImGui(void) const {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

