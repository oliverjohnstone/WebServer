//
// Created by Oliver Johnstone on 06/05/2016.
//

#include "Processor.h"

using namespace HttpServer;

Processor::Processor(Logger &logger, int socket) {
    pConnection = new Connection(logger, socket);
}

Processor::~Processor() {
    delete pConnection;
}

void Processor::run(ThreadPool::ThreadPool *pool) const {
    ThreadPool::Task::run(pool);
}