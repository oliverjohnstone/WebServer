//
// Created by Oliver Johnstone on 04/05/2016.
//

#ifndef WEBSERVER_TASK_H
#define WEBSERVER_TASK_H

#include <iostream>
#include "ThreadPool.h"

using namespace std;

namespace HttpServer {
    namespace ThreadPool {
        class ThreadPool;

        class Task {
        public:
            ~Task();

            virtual void run(HttpServer::ThreadPool::ThreadPool *pool) const;

            void setTaskId(int id);

            int taskId;
        };
    }
}


#endif //WEBSERVER_TASK_H
