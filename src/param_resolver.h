#pragma once

#include <nlohmann/json.hpp>

#include <jinja2cpp/reflected_value.h>
#include <jinja2cpp/value.h>

using json = nlohmann::json;


namespace jinja2 {

struct IParamResolver
{
    virtual ~IParamResolver() = default;

    virtual const ValuesMap ParamsFromFile(const std::string& filePath) = 0;

};

class JsonParamResolver : public IParamResolver
{
public:
    // JsonParamResolver() = default;

    const ValuesMap ParamsFromFile(const std::string& filePath) override
    {
        auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

        return {};
    }


};
    template<>
    struct TypeReflection<JsonParamResolver> : public MapItemAccessor
    {
        json j;


        size_t GetSize() const override
        {
            return j.size();
        }

        bool HasValue(const std::string& name) const override {
            return j.contains(name);
        }

        Value GetValueByName(const std::string& name) const override
        {
            return Value{"j.at(name)"};
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
} // namespace jinja2
