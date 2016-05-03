//
// Created by Oliver Johnstone on 28/04/2016.
//

#include <vector>
#include "Server.h"

void Server::start() {
    for (int i = 0; i < THREAD_POOL_COUNT; i++) {
        ListeningThread *lt = new ListeningThread(this->logger);
        lt->run();
        this->threadPool.push_back(lt);
    }
}

void Server::stop() {
    for (auto th : this->threadPool) {
        th->join();
    }
}

