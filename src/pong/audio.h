#pragma once

#include <miniaudio.h>

#include <string>
#include <unordered_map>

class Audio {
public:
    static bool init(void);
    static void clean(void);

    static void addSound(const std::string &name, const std::string &path);
    static void play(std::string_view filepath);

private:
    Audio() = default;
    ~Audio() = default;

private:
    static ma_engine engine_;
    static std::unordered_map<std::string, std::string> sounds_; // key = name, value = file path
    static bool initialized_;

};

