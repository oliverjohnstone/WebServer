//
// Created by Oliver Johnstone on 06/05/2016.
//

#include "Processor.h"
#include "Request/Request.h"
#include "Response/Response.h"

HttpServer::Processor::Processor(Logger &logger, int socket) {
    pConnection = new Connection(logger, socket);
}

HttpServer::Processor::~Processor() {
    delete pConnection;
}

void HttpServer::Processor::run(ThreadPool::ThreadPool *pool) const {
    HttpServer::Request::Request request(pConnection);
    HttpServer::Response::Response response(request);

    ThreadPool::Task::run(pool);
}