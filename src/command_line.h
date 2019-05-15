#pragma once

#include <string>

namespace jinja2 {

class CommandLine {
public:
    static void RenderTemplate(const std::string& fileName);
};

} // namespace jinja2
