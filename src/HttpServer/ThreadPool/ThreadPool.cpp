//
// Created by Oliver Johnstone on 03/05/2016.
//

#include "ThreadPool.h"

using namespace HttpServer::ThreadPool;

ThreadPool::ThreadPool(int size) {
    this->tasks = new asio::io_service::work(this->ioService);
    for (int i = 0; i < size; i ++) {
        this->threadPool.create_thread(bind(&asio::io_service::run, &this->ioService));
    }

    this->cleaningThread = new std::thread(&ThreadPool::cleanFinishedTasks, this);
}

void ThreadPool::addTask(Task *pTask) {
    int id = this->taskId++;
    pTask->setTaskId(id);
    std::lock_guard<std::mutex> lk(this->mutex);
    this->runningTasks[id] = pTask;
    this->ioService.post(bind(&Task::run, pTask, this));
}

void ThreadPool::stop() {
    this->ioService.stop();
    this->threadPool.join_all();
    this->stopCleanUpThread();
    delete this->tasks;
    this->tasks = nullptr;
}

void ThreadPool::taskFinished(int taskId) {
    std::lock_guard<std::mutex> lk(this->mutex);
    this->finishedTasks.push_back(taskId);
}

void ThreadPool::cleanFinishedTasks() {
    while (this->running) {
        std::lock_guard<std::mutex> lk(this->mutex);
        this->cleanFinished();
    }
}

void ThreadPool::stopCleanUpThread() {
    this->running = false;
    this->cleaningThread->join();
    this->cleanFinished();
}

void ThreadPool::cleanFinished() {
    for (std::vector<int>::iterator it = this->finishedTasks.begin(); it != this->finishedTasks.end(); ++it) {
        delete this->runningTasks[*it];
        this->runningTasks[*it] = nullptr;
    }

    this->finishedTasks.clear();
}