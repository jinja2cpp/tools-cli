#include "param_resolver.h"

#include <nlohmann/json.hpp>

namespace jinja2 {

class JsonParamResolver : public IParamResolver
{
public:
    // JsonParamResolver() = default;

    const ValuesMap ParamsFromFile(const std::string& filePath) override
    {
        using json = nlohmann::json;
        auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

        return {};
    }

};

} // namespace jinja2
