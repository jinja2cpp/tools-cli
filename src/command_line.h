#pragma once

#include <jinja2cpp/template.h>

#include <string>

namespace jinja2 {

class CommandLine {
public:
    explicit CommandLine(std::unique_ptr<Template> tpl = std::make_unique<Template>());

    int Execute(int argc, char **argv);

protected:
    std::string Help();
    std::string Version();
    void RenderTemplate(const std::string& fileName);

private:
    std::unique_ptr<Template> m_tpl;
};

} // namespace jinja2
