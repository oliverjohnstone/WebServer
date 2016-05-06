//
// Created by Oliver Johnstone on 28/04/2016.
//

#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H


#include "../Logger/Logger.h"
#include "../Config/Config.h"
#include "ThreadPool/ThreadPool.h"
#include <thread>

using namespace std;

class Server {

public:
    Server(Config &config, Logger &logger) : config{config}, logger{logger} {};
    void start();
    void stop();
    void threadLoop() const;

private:
    Config &config;
    Logger &logger;
    ThreadPool *threadPool;
    bool running = true;
};


#endif //WEBSERVER_SERVER_H
