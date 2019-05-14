#include <iostream>
#include <boost/program_options.hpp>



int main(int argc, char **argv) {
    std::string help{R"raw(Usage: jinja2 [options] <input template> <input data>

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


    std::cout << help << std::endl;
    return 0;
}

