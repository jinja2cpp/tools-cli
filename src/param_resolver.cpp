#include "param_resolver.h"

// #include <jinja2cpp/template.h>
#include <jinja2cpp/binding/nlohmann_json.h>

using json = nlohmann::json;

namespace jinja2 {

const ValuesMap JsonParamResolver::ParamsFromFile(const std::string &filePath)
{
    nlohmann::json values = {
            {"message", "Hello World from Parser!"}
    };
    auto x = Reflect(std::move(values));
    return {{"params", x}};
}

} // namespace jinja2
