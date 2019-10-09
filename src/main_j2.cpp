#include "command_line.h"

int main(int argc, char* argv[]) {
    jinja2::CommandLineJ2 cli;
    return cli.Execute(argc, argv);
}
