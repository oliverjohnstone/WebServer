//
// Created by Oliver Johnstone on 06/05/2016.
//

#ifndef WEBSERVER_PROCESSOR_H
#define WEBSERVER_PROCESSOR_H

#include "ThreadPool/Task.h"
#include "../Logger/Logger.h"
#include "Connection.h"
#include "Router/Router.h"

namespace HttpServer {

    class Processor : public ThreadPool::Task {

    public:
        Processor(Logger &logger, int socket, HttpServer::Router::Router &router);

        ~Processor();

        void run(ThreadPool::ThreadPool *pool) const;

    private:
        Connection *pConnection;
        HttpServer::Router::Router &router;
    };
}


#endif //WEBSERVER_PROCESSOR_H
