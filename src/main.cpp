#include "command_line.h"

int main(int argc, char* argv[]) {
    jinja2::CommandLine cli;
    return cli.Execute(argc, argv);
}
