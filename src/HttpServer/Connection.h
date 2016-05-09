//
// Created by Oliver Johnstone on 07/05/2016.
//

#ifndef WEBSERVER_CONNECTION_H
#define WEBSERVER_CONNECTION_H

#include "../Logger/Logger.h"
#include <unistd.h>

#define BUFFER_SIZE 500

namespace HttpServer {

    class Connection {
    public:
        Connection(Logger &logger, int socket);

        ~Connection();

        string readLine();

        int writeLine(string line);

        int writeBuffer(char *buffer, int size);

        int readBuffer(char *buffer, int size);

        void flush();

        void closeSocket();

        int getTotalBytesSent();

        bool isOpen();

    private:
        int socket;
        int bytesSent = 0;
        int currentOutBufferSize = 0;
        int currentInBufferSize = 0;
        bool isSocketOpen = false;
        bool eof = false;
        char outBuffer[BUFFER_SIZE];
        char inBuffer[BUFFER_SIZE];
        Logger logger;

        int readFromSocket();

        int writeToSocket(char *buffer, int size);
    };
}

#endif //WEBSERVER_CONNECTION_H
