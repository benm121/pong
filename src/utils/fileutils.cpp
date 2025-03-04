#include "fileutils.h"
#include "log.h"

#include <ctime>
#include <fstream>
#include <sys/stat.h>

namespace fileutils {

std::optional<std::string> readToString(std::string_view filepath) {

    std::ifstream file(filepath.data(), std::ios::ate);
    if (!file.is_open()) {
        LOG_ERROR("failed to open file %s", filepath.data());
        return std::nullopt;
    }

    size_t size = file.tellg();

    std::string contents(size, '\0');
    file.seekg(0, std::ios::beg);

    if (!file.read(contents.data(), size)) {
        LOG_ERROR("failed to read file %s", filepath.data());
        return std::nullopt;
    }
    return contents;
}

bool write(std::string_view filepath, const std::string &content) {

    std::ofstream file(filepath.data(), std::ios::ate);
    if (!file.is_open()) {
        LOG_ERROR("failed to open file %s", filepath.data());
        return false;
    }

    if (!file.write(content.data(), content.size())) {
        LOG_ERROR("failed to write to file %s", filepath.data());
        return false;
    }

    return true;
}

std::optional<long> getTimestamp(std::string_view filepath) {

    struct stat fileInfo;

    if (stat(filepath.data(), &fileInfo) != 0) {
        return std::nullopt;
    }
    return fileInfo.st_mtime;
}

} // namespace fileutils

