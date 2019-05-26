#include "param_resolver.h"

#include <nlohmann/json.hpp>

#include <jinja2cpp/reflected_value.h>

using json = nlohmann::json;

namespace jinja2 {

const ValuesMap JsonParamResolver::ParamsFromFile(const std::string &filePath)
{
    auto j = json::parse("{ \"happy\": true, \"pi\": 3.141 }");
    return {{"params", Value(jinja2::Reflect(j))}};
}

namespace detail {

struct JsonAccessor : public MapItemAccessor
{
    json j;

    explicit JsonAccessor(const json &val) : j(val) {}
    ~JsonAccessor() override = default;

    size_t GetSize() const override
    {
        return j.size();
    }

    bool HasValue(const std::string& name) const override {
        return j.contains(name);
    }

    Value GetValueByName(const std::string& name) const override
    {
        return Value{"j.at(name)"}; // TODO: convert json::value to jinja2::Value. use visitor?
    }

    std::vector<std::string> GetKeys() const override
    {
        std::vector<std::string> result;
        for (auto& item : j.items())
        {
            result.emplace_back(item.key());
        }
        return result;
    }
};

template<>
struct Reflector<json> {
    static auto Create(const json &val) {
        auto ac = JsonAccessor(val);
        return GenericMap([accessor = JsonAccessor(val)]() { return &accessor; });
    }

    static auto CreateFromPtr(const json *val) {
        return GenericMap([accessor = JsonAccessor(*val)]() { return &accessor; });
    }

};

} // namespace detail

} // namespace jinja2
