//
// Created by Oliver Johnstone on 28/04/2016.
//

#ifndef WEBSERVER_SERVER_H
#define WEBSERVER_SERVER_H


#include "../Logger/Logger.h"
#include "../Config/Config.h"
#include "ListeningThread/ListeningThread.h"
#include <array>
#include <vector>

using namespace std;

const int THREAD_POOL_COUNT = 50;

class Server {

public:
    Server(Config &config, Logger &logger) : config{config}, logger{logger} {};
    void start();
    void stop();

private:
    Config &config;
    Logger &logger;

    vector<ListeningThread*> threadPool;
};


#endif //WEBSERVER_SERVER_H
