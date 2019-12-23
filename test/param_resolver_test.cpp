#include "../src/param_resolver.h"

#include <gmock/gmock.h>

using namespace testing;
using namespace jinja2;

TEST(ParamResolver, ResolveJson)
{
    JsonParamResolver resolver;
    auto params = resolver.ParamsFromFile("");

    try {
        auto m = params["params"];

        ASSERT_TRUE(m.isMap());

        //auto genmap = nonstd::get_if<GenericMap>(&m)

        for (auto el : params) {
            std::cout << el.first << std::endl;
            // ASSERT_EQ(std::string("j.at(name)"), el);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

}