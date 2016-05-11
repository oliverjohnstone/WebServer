#include <iostream>
#include "src/Config/Config.h"
#include "src/Config/ProgramOptions.h"
#include "src/Logger/Logger.h"
#include "src/HttpServer/Server.h"

int main(int argc, char **argv) {
    Logger logger;
    int exitCode = 0;

    try {
        ProgramOptions options(argc, argv);

        if (options.isHelp()) {
            cout << options.getHelp() << endl;
            exitCode = 1;
        } else {
            Config config(options.getConfigPath());
            HttpServer::Server server(config, logger);
            server.start();
        }
    } catch (std::exception &e) {
//        logger.error(e.what());
        exitCode = 2;
    }

    logger.info("Exiting");
    logger.flush();
    return exitCode;
}