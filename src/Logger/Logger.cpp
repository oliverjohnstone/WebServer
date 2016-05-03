//
// Created by Oliver Johnstone on 27/04/2016.
//

#include <iostream>
#include "Logger.h"

void Logger::info(string msg) {
    this->log(msg, LEVEL::INFO);
}

void Logger::error(string msg) {
    this->log(msg, LEVEL::ERROR);
}

void Logger::warn(string msg) {
    this->log(msg, LEVEL::WARN);
}

void Logger::log(string msg, LEVEL levelCode) {
    string level;

    switch (levelCode) {
        case LEVEL::INFO: level = "Info"; break;
        case LEVEL::WARN: level = "Warn"; break;
        case LEVEL::ERROR: level = "Error"; break;
        default: level = "Info";
    }

    this->logLines[this->currentLogLine++] = this->getFormattedLine(level, msg);

    if (this->currentLogLine == MAX_LOG_LINES) this->flush();
}

char *Logger::getDateTimeString() {
    time_t tm = time(NULL);
    char *str = asctime(localtime(&tm));
    str[strlen(str) -1] = 0;
    return str;
}

bool Logger::flush() {
    if (this->currentLogLine == 0) return false;

    for (int i = 0; i < this->currentLogLine; i++) {
        cout << this->logLines[i];
        delete this->logLines[i];
        this->logLines[i] = nullptr;
    }

    this->currentLogLine = 0;

    return true;
}

char *Logger::getFormattedLine(string level, string message) {
    char *dateTime = this->getDateTimeString();
    size_t length = strlen(dateTime) + strlen(level.c_str()) + strlen(message.c_str());
    int formatChars = 6;
    char *formatted = new char[length + formatChars];

    sprintf(formatted, "[%s] %s: %s\n", dateTime, level.c_str(), message.c_str());

    return formatted;
}