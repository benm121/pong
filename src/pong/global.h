#pragma once

#include <cstdint>
#include <filesystem>

namespace global {

constexpr uint32_t SCREEN_WIDTH = 1000;
constexpr uint32_t SCREEN_HEIGHT = 750;
extern std::filesystem::path execPath; // declared in main before Game

} // namespace global

