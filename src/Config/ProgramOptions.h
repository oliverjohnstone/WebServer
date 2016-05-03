//
// Created by Oliver Johnstone on 27/04/2016.
//

#ifndef WEBSERVER_PROGRAMOPTIONS_H
#define WEBSERVER_PROGRAMOPTIONS_H

#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace std;

class ProgramOptions {
public:
    ProgramOptions(int argc, char **argv);
    string getConfigPath();
    bool isHelp();
    string getHelp();

private:
    po::options_description description;
    po::variables_map vm;
};


#endif //WEBSERVER_PROGRAMOPTIONS_H
