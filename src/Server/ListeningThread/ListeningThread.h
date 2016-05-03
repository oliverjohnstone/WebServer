//
// Created by Oliver Johnstone on 28/04/2016.
//

#ifndef WEBSERVER_LISTENINGTHREAD_H
#define WEBSERVER_LISTENINGTHREAD_H

#include <iostream>
#include <thread>
#include "../../Logger/Logger.h"
#include "Runner.h"

using namespace std;

class ListeningThread {
public:

    ListeningThread(Logger logger);
    void run();
    void join();
    bool isFree();
    void pushJob();

private:
    std::thread *thread;
    shared_ptr<Runner> runner;
    std::promise<FUTURE_FLAG> thread_comm;
    Logger logger;
};

#endif //WEBSERVER_LISTENINGTHREAD_H
