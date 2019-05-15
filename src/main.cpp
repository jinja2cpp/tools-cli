#include "command_line.h"

#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char **argv) {

    po::options_description desc("Options");

    desc.add_options()
            ("help,h", "Display this help message")
            ("version,v", "Display the version number")
            ("format", "Format of input variables: auto, ini, json")
            ("input-template", po::value<std::vector<std::string>>(), "Input template file path")
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
            std::cout << "Usage: jinja2cpp [options] <input template> <input data>" << std::endl
                      << desc << std::endl;
            return 1;
        }

//        for (auto &v : vm["input-data"].as<std::vector<std::string> >())
//        {
//            if (vm.count("input-data")) {
//                std::cout << "Input data are: ";
//                std::cout << v << std::endl;
//            }
//        }


        if (vm.count("input-template"))
        {
            const auto &filename = vm["input-template"].as<std::vector<std::string> >()[0];
            jinja2::CommandLine::RenderTemplate(filename);

        }

    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
