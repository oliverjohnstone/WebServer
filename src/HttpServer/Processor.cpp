//
// Created by Oliver Johnstone on 06/05/2016.
//

#include "Processor.h"
#include "Request/Request.h"

HttpServer::Processor::Processor(Logger &logger, int socket) {
    pConnection = new Connection(logger, socket);
}

HttpServer::Processor::~Processor() {
    delete pConnection;
}

void HttpServer::Processor::run(ThreadPool::ThreadPool *pool) const {
    Request::Request request(pConnection);

    ThreadPool::Task::run(pool);
}