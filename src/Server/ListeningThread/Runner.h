//
// Created by Oliver Johnstone on 29/04/2016.
//

#ifndef WEBSERVER_RUNNER_H
#define WEBSERVER_RUNNER_H

#include <future>
#include "../../Logger/Logger.h"

enum FUTURE_FLAG {
    NEW_TASK,
    QUIT
};

class Runner {
public:
    void run(Logger logger, std::future<FUTURE_FLAG> future) const;
    void processTask() const;
};

#endif //WEBSERVER_RUNNER_H
