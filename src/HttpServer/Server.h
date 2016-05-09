//
// Created by Oliver Johnstone on 28/04/2016.
//

#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H


#include "../Logger/Logger.h"
#include "../Config/Config.h"
#include "ThreadPool/ThreadPool.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include "Processor.h"

using namespace std;

namespace HttpServer {

    class Server {

    public:
        Server(Config &config, Logger &logger) : config{config}, logger{logger} { };

        void start();

        void stop();

    private:
        Config &config;
        Logger &logger;
        ThreadPool::ThreadPool *threadPool;
        bool running = true;
        int socket;

        int openSocket(int portNumber);

        void socketError(const char *msg, bool shouldThrow = true);

        struct sockaddr_in getServerAddress(int port);
    };
}

#endif //WEBSERVER_SERVER_H
