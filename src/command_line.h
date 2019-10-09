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

/**
 * CommandLine is analog CLI of python jinja2-cli
 */
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

/**
 * CommandLine is analog CLI of modern python j2cli (https://github.com/kolypto/j2cli)
 */
class CommandLineJ2 : protected ICommands {
public:
    explicit CommandLineJ2(std::unique_ptr<Template> tpl = std::make_unique<Template>());

    int Execute(int argc, char **argv);

protected:
    std::string Help() override ;
    std::string Version() override;
    void RenderTemplate(const std::string& fileName) override;

private:
    std::unique_ptr<Template> m_tpl;
};

} // namespace jinja2
