#pragma once

#include <functional>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <cstdint>

namespace ui {

using MenuFunc = std::function<void()>;

// takes in functions to call when singleplayer or multiplayer is selected
void drawMenu(MenuFunc spFunc, MenuFunc mpFunc, MenuFunc quitFunc);

void drawScore(uint32_t score, float xPos, float yPos);

} // namespace ui

