//
// Created by Oliver Johnstone on 04/05/2016.
//

#ifndef WEBSERVER_TASK_H
#define WEBSERVER_TASK_H

#include <iostream>
#include "ThreadPool.h"

using namespace std;

class ThreadPool;

namespace HttpServer {
    namespace ThreadPool {
        class Task {
        public:
            ~Task();

            void run(ThreadPool *pool) const;

            void setTaskId(int id);

            int taskId;
        };
    }
}


#endif //WEBSERVER_TASK_H
