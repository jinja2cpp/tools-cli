#include "CLI/CLI.hpp"

#include <iostream>



int main(int argc, char **argv) {
    CLI::App test{R"raw(Usage: jinja2 [options] <input template> <input data>

Options:
--version             show program's version number and exit
-h, --help            show this help message and exit
--format=FORMAT       format of input variables: auto, ini, json,
querystring
-e EXTENSIONS, --extension=EXTENSIONS
extra jinja2 extensions to load
-D key=value          Define template variable in the form of key=value
                                                                  -s SECTION, --section=SECTION
Use only this section from the configuration
--strict              Disallow undefined variables to be used within the template)raw"};

    // Remove help flag because it shortcuts all processing
    test.set_help_flag();

    // Add custom flag that activates help
    auto help = test.add_flag("-h,--help", "Request help");

//    std::string some_option;
//    test.add_option("-a", some_option, "Some description");

    try {
        test.parse(argc, argv);
        if(*help)
            throw CLI::CallForHelp();
    } catch(const CLI::Error &e) {
//        std::cout << "Option -a string in help: " << some_option << std::endl;
        return test.exit(e);
    }

//    std::cout << "Option -a string: " << some_option << std::endl;
    return 0;
}

