//
// Created by Oliver Johnstone on 29/04/2016.
//

#include "Runner.h"
#include <iostream>

void Runner::run(Logger logger, std::future<FUTURE_FLAG> future) const {
    while (true) {
        future.wait();
        switch (future.get()) {
            case FUTURE_FLAG::NEW_TASK:
                this->processTask();
                break;
            case FUTURE_FLAG::QUIT:
                return;
            default:
                logger.error("Unrecognised future flag passed to listening thread");
                return;
        }
    }
}

void Runner::processTask() const {
    cout << "Hello World" << endl;
}