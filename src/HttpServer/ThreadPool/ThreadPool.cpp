//
// Created by Oliver Johnstone on 03/05/2016.
//

#include "ThreadPool.h"

HttpServer::ThreadPool::ThreadPool::ThreadPool(int size) {
    this->tasks = new asio::io_service::work(this->ioService);
    for (int i = 0; i < size; i ++) {
        this->threadPool.create_thread(bind(&asio::io_service::run, &this->ioService));
    }

    this->cleaningThread = new std::thread(&ThreadPool::cleanFinishedTasks, this);
}

void HttpServer::ThreadPool::ThreadPool::addTask(Task *pTask) {
    int id = this->taskId++;
    pTask->setTaskId(id);
    std::lock_guard<std::mutex> lk(this->mutex);
    this->runningTasks[id] = pTask;
    this->ioService.post(bind(&Task::run, pTask, this));
}

void HttpServer::ThreadPool::ThreadPool::stop() {
    this->ioService.stop();
    this->threadPool.join_all();
    this->stopCleanUpThread();
    delete this->tasks;
    this->tasks = nullptr;
}

void HttpServer::ThreadPool::ThreadPool::taskFinished(int taskId) {
    std::lock_guard<std::mutex> lk(this->mutex);
    this->finishedTasks.push_back(taskId);
}

void HttpServer::ThreadPool::ThreadPool::cleanFinishedTasks() {
    while (this->running) {
        std::lock_guard<std::mutex> lk(this->mutex);
        this->cleanFinished();
    }
}

void HttpServer::ThreadPool::ThreadPool::stopCleanUpThread() {
    this->running = false;
    this->cleaningThread->join();
    this->cleanFinished();
}

void HttpServer::ThreadPool::ThreadPool::cleanFinished() {
    for (std::vector<int>::iterator it = this->finishedTasks.begin(); it != this->finishedTasks.end(); ++it) {
        delete this->runningTasks[*it];
        this->runningTasks[*it] = nullptr;
    }

    this->finishedTasks.clear();
}