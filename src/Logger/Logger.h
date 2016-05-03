//
// Created by Oliver Johnstone on 27/04/2016.
//

#ifndef WEBSERVER_LOGGER_H
#define WEBSERVER_LOGGER_H

#include <string>
#include <array>

using namespace std;

const int MAX_LOG_LINES = 30;

class Logger {

public:
    void info(string msg);
    void error(string msg);
    void warn(string msg);
    bool flush();

private:
    enum LEVEL { INFO, ERROR, WARN };
    array<char *, MAX_LOG_LINES> logLines;
    int currentLogLine = 0;

    void log(string msg, LEVEL colour);
    char *getDateTimeString();
    char *getFormattedLine(string level, string message);
};

#endif //WEBSERVER_LOGGER_H
