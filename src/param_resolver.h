#pragma once

//#include "yaml_reflector.h"
#include <jinja2cpp/value.h>

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

    const ValuesMap ParamsFromFile(const std::string& filePath) override;


};



} // namespace jinja2
