#include "command_line.h"

#include <jinja2cpp/template.h>
#include <rapidjson/document.h>

namespace jinja2
{

void CommandLine::RenderTemplate(const std::string& fileName)
{
    jinja2::Template tpl;
    auto result = tpl.LoadFromFile(fileName);
    if (!result.has_value()) {
        std::cout << result.error() << std::endl;
    }

    std::cout << "Input template is: ";
    std::cout << fileName << std::endl;

    tpl.Render(std::cout, {});
}

    void parceOptions() {
        rapidjson::Document document;
//    document.Parse()
//
//    for (auto& v : a.GetArray())
//        printf("%d ", v.GetInt());
    }

} // namespace jinja2
