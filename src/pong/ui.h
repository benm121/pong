#pragma once

#include <cstdint>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace ui {

void drawScore(uint32_t score, float xPos, float yPos);

} // namespace ui

