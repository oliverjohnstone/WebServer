#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include "src/Config/Config.h"
#include "src/Config/ProgramOptions.h"
#include "src/Logger/Logger.h"
#include "src/Server/Server.h"

void setupCancelSigHandler();

int main(int argc, char** argv) {
    Logger logger;
    int exitCode = 0;

    try {
        ProgramOptions options(argc, argv);

        if (options.isHelp()) {
            cout << options.getHelp() << endl;
            exitCode = 1;
        } else {
            Config config(options.getConfigPath());
            Server server(config, logger);
            setupCancelSigHandler();
            server.start();
        }
    } catch (std::exception &e) {
        logger.error(e.what());
        exitCode = 2;
    }

    logger.info("Exiting");
    logger.flush();
    return exitCode;
}

void sigHandler(int signal) {
    cout << signal << endl;
}

void setupCancelSigHandler() {
    signal(SIGINT, &sigHandler);
//    struct sigaction sigIntHandler;
//    sigIntHandler.sa_handler = sigHandler;
//    sigemptyset(&sigIntHandler.sa_mask);
//    sigIntHandler.sa_flags = 0;
//
//    sigaction(SIGINT, &sigIntHandler, NULL);
}