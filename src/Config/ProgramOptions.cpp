//
// Created by Oliver Johnstone on 27/04/2016.
//

#include <iostream>
#include "ProgramOptions.h"

string ProgramOptions::getConfigPath() {
    return this->vm.count("config") ? this->vm["config"].as<string>() : "config.ini";
}

ProgramOptions::ProgramOptions(int argc, char **argv) : description("Allowed Options"), vm() {
    this->description.add_options()
            ("help", "display help message")
            ("config", po::value<string>(), "configuration path");

    po::store(parse_command_line(argc, argv, this->description), this->vm);
    po::notify(this->vm);
}

bool ProgramOptions::isHelp() {
    return this->vm.count("help") > 0;
}

string ProgramOptions::getHelp() {
    this->description;
}
