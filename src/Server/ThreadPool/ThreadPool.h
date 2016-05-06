//
// Created by Oliver Johnstone on 03/05/2016.
//

#ifndef WEBSERVER_THREADPOOL_H
#define WEBSERVER_THREADPOOL_H

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include "Task.h"
#include <vector>
#include <unordered_map>
#include <thread>
#include <condition_variable>

using namespace boost;

class Task;

class ThreadPool {
public:
    ThreadPool(int size);
    void addTask(Task *pTask);
    void stop();
    void stopTasks();

    void taskFinished(int taskId);

private:
    boost::asio::io_service ioService;
    boost::thread_group threadPool;
    boost::asio::io_service::work *tasks;
    std::thread *cleaningThread;
    std::unordered_map<int, Task *> runningTasks;
    std::vector<int> finishedTasks;
    int taskId = 0;
    std::mutex mutex;
    bool running = true;

    void cleanFinishedTasks();
    void stopCleanUpThread();
    void cleanFinished();
};


#endif //WEBSERVER_THREADPOOL_H
