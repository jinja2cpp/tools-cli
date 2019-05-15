#include "../src/command_line.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
using namespace jinja2;

class MockTemplate : public Template
{
public:
    MOCK_METHOD2(Load, ParseResult(const char* tpl, std::string tplName));
    MOCK_METHOD2(Load, ParseResult(const std::string& str, std::string tplName));
    MOCK_METHOD2(Load, ParseResult(std::istream& stream, std::string tplName));

    MOCK_METHOD1(LoadFromFile, ParseResult (const std::string& fileName));
    MOCK_METHOD2(Render, void (std::ostream& os, const ValuesMap& params));
    MOCK_METHOD1(RenderAsString, std::string (const ValuesMap& params));
};

TEST(CommandLine, Execute_without_args_expect_show_help)
{
    MockTemplate tpl;
    // EXPECT_CALL(tpl, Load(std::string("123"), std::string("321"))).WillOnce(Return(ParseResult{}));

    //Template t = static_cast<Template>(tpl);
    CommandLine cli(std::make_unique<Template>(tpl));
    //auto argv =  *char[2]{"sf", "qeqwe"};

    ASSERT_EQ(EXIT_FAILURE, cli.Execute(1, nullptr));

}

TEST(CommandLine, Execute_help)
{
    MockTemplate tpl;
    // EXPECT_CALL(tpl, Load(std::string("123"), std::string("321"))).WillOnce(Return(ParseResult{}));

    //Template t = static_cast<Template>(tpl);
    CommandLine cli(std::make_unique<Template>(tpl));
    //auto argv =  *char[2]{"sf", "version"};

    // TODO: expect call Version()
    ASSERT_EQ(EXIT_SUCCESS, cli.Execute(1, nullptr));
}

TEST(CommandLine, Execute_version)
{
    MockTemplate tpl;
    // EXPECT_CALL(tpl, Load(std::string("123"), std::string("321"))).WillOnce(Return(ParseResult{}));

    //Template t = static_cast<Template>(tpl);
    CommandLine cli(std::make_unique<Template>(tpl));
    //auto argv =  *char[2]{"sf", "version"};

    // TODO: expect call Version()
    ASSERT_EQ(EXIT_SUCCESS, cli.Execute(1, nullptr));
}