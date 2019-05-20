#pragma once

#include <jinja2cpp/template.h>

#include <string>

namespace jinja2 {

struct ICommands {
    virtual ~ICommands() = default;

    virtual std::string Help() = 0;
    virtual std::string Version() = 0;
    virtual void RenderTemplate(const std::string& fileName) = 0;
};

class CommandLine : protected ICommands {
public:
    explicit CommandLine(std::unique_ptr<Template> tpl = std::make_unique<Template>());

    int Execute(int argc, char **argv);

protected:
    std::string Help() override ;
    std::string Version() override;
    void RenderTemplate(const std::string& fileName) override;

private:
    std::unique_ptr<Template> m_tpl;
};

} // namespace jinja2
