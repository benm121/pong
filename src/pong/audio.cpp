#include "audio.h"
#include "global.h"
#include "utils/log.h"

ma_engine Audio::engine_;
std::unordered_map<std::string, std::string> Audio::sounds_;
bool Audio::initialized_ = false;

bool Audio::init(void) {
    ma_result result = ma_engine_init(nullptr, &engine_);
    if (result != MA_SUCCESS) {
        return false;
    }
    initialized_ = true;
    return true;
}

void Audio::clean(void) {
    if (initialized_) {
        sounds_.clear();
        ma_engine_uninit(&engine_);
    }
}

void Audio::addSound(const std::string &name, const std::string &path) {
    if (!initialized_) {
        LOG_WARN("cannot add sound: audio not initialized");
        return;
    }
    sounds_[name] = global::execPath.string() + path;
}

void Audio::play(std::string_view name) {
    if (!initialized_) {
        LOG_WARN("cannot play sound: audio not initialized");
        return;
    }

    if (sounds_.find(name.data()) == sounds_.end()) {
        LOG_ERROR("could not find sound \"%s\"", name.data());
        return;
    }

    if (ma_engine_play_sound(&engine_, sounds_[name.data()].data(), nullptr)) {
        LOG_ERROR("failed to play sound \"%s\"", name.data());
    }
}

