
#include <optional>
#include <string>

namespace fileutils {

std::optional<std::string> readToString(std::string_view filepath);

bool write(std::string_view filepath, const std::string &content);

std::optional<long> getTimestamp(std::string_view filepath);

} // namespace fileutils

