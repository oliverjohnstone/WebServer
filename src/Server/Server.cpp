//
// Created by Oliver Johnstone on 28/04/2016.
//

#include "Server.h"

void Server::start() {
    this->threadPool = new ThreadPool(this->config.getConcurrentConnections());
    this->threadPool->addTask(new Task);
    this->threadPool->addTask(new Task);
    this->threadPool->addTask(new Task);
    while (this->running) {

    }
}

void Server::stop() {
    this->running = false;
    this->threadPool->stop();
}