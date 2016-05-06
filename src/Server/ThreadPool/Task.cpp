//
// Created by Oliver Johnstone on 04/05/2016.
//

#include "Task.h"

void Task::run(ThreadPool *pool) const {
    cout << "Hello World" << endl;
    pool->taskFinished(this->taskId);
}

void Task::setTaskId(int id) {
    this->taskId = id;
}

Task::~Task() {
//    DELETE any allocated resources here
    cout << "Destructor: " << this->taskId << endl;
}





