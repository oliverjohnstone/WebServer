//
// Created by Oliver Johnstone on 06/05/2016.
//

#ifndef WEBSERVER_PROCESSOR_H
#define WEBSERVER_PROCESSOR_H

#include "ThreadPool/Task.h"
#include "../Logger/Logger.h"
#include "Connection.h"

namespace HttpServer {

    class Processor : public ThreadPool::Task {
    public:
        Processor(Logger &logger, int socket);

        ~Processor();

        void run(ThreadPool::ThreadPool *pool) const;

    private:
        Connection *pConnection;
    };
}


#endif //WEBSERVER_PROCESSOR_H
