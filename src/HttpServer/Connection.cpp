//
// Created by Oliver Johnstone on 07/05/2016.
//

#include "Connection.h"
#include <errno.h>

#define NEW_LINE '\n'

using namespace HttpServer;

Connection::~Connection() {
    closeSocket();
}

string Connection::readLine() {
    string line;
    int i = 0;
    bool foundNewLineChar = false;

    do {
        while (inBuffer[i] != NEW_LINE && inBuffer[i] != 0 && i < BUFFER_SIZE) {
            line.push_back(inBuffer[i++]);
        }

        if(inBuffer[i] == NEW_LINE) {
            foundNewLineChar = true;
            int from = i + 1;
            memmove(inBuffer, &inBuffer[from], (size_t)BUFFER_SIZE - from);
            inBuffer[BUFFER_SIZE - from] = 0;
        } else {
            if (readFromSocket() == 0) {
                // End of stream
                break;
            }
        }
    } while (!foundNewLineChar);

    return line;
}

int Connection::readFromSocket() {
    if (eof) return 0;
    int start = currentInBufferSize == 0 ? 0 : currentInBufferSize - 1;
    ssize_t bytesRead = read(socket, &inBuffer[start], (size_t)BUFFER_SIZE - currentInBufferSize - 1);

    if (bytesRead == 0) {
        inBuffer[0] = 0;
        eof = true;
        return 0;
    }

    if (bytesRead < 0) {
        char err[500];
        sprintf(err, "Error reading from socket: %s", strerror(errno));
        this->logger.error(err);
    }

    currentInBufferSize += bytesRead;

    if (inBuffer[currentInBufferSize - 1] == 0) eof = true;
    else inBuffer[currentInBufferSize] = 0;

    return (int)bytesRead;
}

int Connection::writeLine(string line) {
    int length = (int)line.length();
    if (currentOutBufferSize + length >= BUFFER_SIZE - 2) {
        flush();
        return writeToSocket((char *)line.c_str(), length);
    } else {
        memcpy(&outBuffer[currentOutBufferSize], line.c_str(), (size_t)length);
        currentOutBufferSize += length;
        outBuffer[currentOutBufferSize] = '\n';
        outBuffer[++currentOutBufferSize] = 0;
        return length;
    }
}

int Connection::writeBuffer(char *buffer, int size) {
    if (currentOutBufferSize + size >= BUFFER_SIZE - 1) {
        flush();
        return writeToSocket(buffer, size);
    } else {
        memcpy(&outBuffer[currentOutBufferSize], buffer, (size_t)size);
        currentOutBufferSize += size;
        outBuffer[currentOutBufferSize++] = 0;
        return size;
    }
}

int Connection::writeToSocket(char *buffer, int size) {
    int written = (int)write(socket, buffer, (size_t)size);
    if (written < 0) {
        char err[500];
        sprintf(err, "Error writing to socket: %s", strerror(errno));
        this->logger.error(err);
        throw std::runtime_error("Error writing to socket");
    }
    bytesSent += written;
    return written;
}

void Connection::flush() {
    writeToSocket(outBuffer, currentOutBufferSize);
}

void Connection::closeSocket() {
    if (isSocketOpen) {
        flush();
        close(socket);
        eof = true;
        isSocketOpen = false;
    }
}

int Connection::getTotalBytesSent() {
    return bytesSent;
}

int Connection::readBuffer(char *buffer, int size) {
    int i = 0;

    do {
        while (inBuffer[i] != 0 && i < BUFFER_SIZE) {
            buffer[i] = inBuffer[i++];
        }

        if (readFromSocket() == 0) {
            // End of stream
            break;
        }
    } while (i < size);

    return 0;
}

bool Connection::isOpen() {
    return isSocketOpen;
}

Connection::Connection(Logger &logger, int socket) : logger(logger) {
    this->socket = socket;
    outBuffer[0] = 0;
    inBuffer[0] = 0;
}

bool Connection::isEof() {
    return eof;
}





