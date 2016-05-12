//
// Created by Oliver Johnstone on 06/05/2016.
//

#include "Processor.h"

HttpServer::Processor::Processor(Logger &logger, int socket, HttpServer::Router::Router &router) : router(router) {
    pConnection = new Connection(logger, socket);
}

HttpServer::Processor::~Processor() {
    delete pConnection;
    ThreadPool::Task::~Task();
}

void HttpServer::Processor::run(ThreadPool::ThreadPool *pool) const {
    HttpServer::Request::Request request(pConnection);
    HttpServer::Response::Response response(request);

    router.route(request, response);
    response.send(pConnection);

    ThreadPool::Task::run(pool);
}