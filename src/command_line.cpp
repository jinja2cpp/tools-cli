#include "command_line.h"
#include "param_resolver.h"
#include <version.h>

#include <boost/program_options.hpp>

#include <iostream>
#include <memory>

namespace jinja2
{

CommandLine::CommandLine(std::unique_ptr<Template> tpl) : m_tpl(std::move(tpl)) { }

int CommandLine::Execute(int argc, char* argv[])
{
    namespace po = boost::program_options;
    po::options_description desc("Options");

    desc.add_options()
            ("help,h", "Display this help message")
            ("version,v", "Display the version number")
            ("format", "Format of input variables: auto, ini, json, yaml, toml")
            ("input-template", po::value<std::string>(), "Input template file path")
            ("input-data", po::value<std::vector<std::string>>(),
             "Define template variable in the form of key=value");

    po::positional_options_description p;
    p.add("input-template", 1);
    p.add("input-data", -1);

    try {
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).allow_unregistered().run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << Help() << std::endl << desc << std::endl;
            return EXIT_FAILURE;
        }

        if (vm.count("version")) {
            std::cout << Version() << std::endl;
            return EXIT_SUCCESS;
        }

        for (auto &v : vm["input-data"].as<std::vector<std::string> >())
        {
            if (vm.count("input-data")) {
                std::cout << "Input data are: ";
                std::cout << v << std::endl;
            }
        }


        if (vm.count("input-template"))
        {
            const auto &filename = vm["input-template"].as<std::string>();
            RenderTemplate(filename);
            return EXIT_SUCCESS;
        }

    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}

std::string CommandLine::Help()
{
    return "Usage: jinja2cpp-cli [options] <input template> <input data>";
}

std::string CommandLine::Version()
{
    return jinja2cppVersion;
}


void CommandLine::RenderTemplate(const std::string& fileName)
{
    jinja2::Template tpl;
    auto result = tpl.LoadFromFile(fileName);
    if (!result.has_value()) {
        std::cout << result.error() << std::endl;
    }

    std::cout << "Input template is: ";
    std::cout << fileName << std::endl;


    JsonParamResolver resolver;

    ValuesMap vm = resolver.ParamsFromFile("sample.json");
    tpl.Render(std::cout, vm);
}

} // namespace jinja2
