//
// Created by Oliver Johnstone on 04/05/2016.
//

#include "Task.h"

void HttpServer::ThreadPool::Task::run(HttpServer::ThreadPool::ThreadPool *pool) const {
    pool->taskFinished(this->taskId);
}

void HttpServer::ThreadPool::Task::setTaskId(int id) {
    this->taskId = id;
}

HttpServer::ThreadPool::Task::~Task() {
//    DELETE any allocated resources here
    cout << "Destructor: " << this->taskId << endl;
}





