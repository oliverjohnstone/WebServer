//
// Created by Oliver Johnstone on 04/05/2016.
//

#include "Task.h"

using namespace HttpServer::ThreadPool;

void Task::run(ThreadPool *pool) const {
    pool->taskFinished(this->taskId);
}

void Task::setTaskId(int id) {
    this->taskId = id;
}

Task::~Task() {
//    DELETE any allocated resources here
    cout << "Destructor: " << this->taskId << endl;
}





