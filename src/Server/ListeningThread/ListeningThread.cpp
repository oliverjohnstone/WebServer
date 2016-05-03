//
// Created by Oliver Johnstone on 28/04/2016.
//

#include <thread>
#include <future>
#include "ListeningThread.h"

void ListeningThread::run() {
    this->runner = shared_ptr<Runner>(new Runner);
    this->thread = new std::thread(&Runner::run, runner, this->logger, this->thread_comm.get_future());
}

void ListeningThread::join() {
    this->thread_comm.set_value(FUTURE_FLAG::)
    this->thread->join();
    delete this->runner.get();
    delete this->thread;
}

ListeningThread::ListeningThread(Logger logger) {
    this->logger = logger;
}



