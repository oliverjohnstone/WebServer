//
// Created by Oliver Johnstone on 28/04/2016.
//

#include "Server.h"

using namespace HttpServer;

void Server::start() {
    socket = this->openSocket(this->config.getPort());

    this->threadPool = new ThreadPool(this->config.getConcurrentConnections());

    while (this->running) {
        struct sockaddr_in clientAddress;
        socklen_t clientLength = sizeof(clientAddress);
        int clientSocket = accept(socket, (struct sockaddr *) &clientAddress, &clientLength);
        if (clientSocket < 0) this->socketError("Error opening client socket", false);

        Processor *processor = new Processor(logger, clientSocket);
        threadPool->addTask(processor);
    }
}

void Server::stop() {
    this->running = false;
    this->threadPool->stop();
    close(socket);
}

int Server::openSocket(int portNumber) {
    int sockFd;
    sockaddr_in serverAddress = this->getServerAddress(portNumber);

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) this->socketError("Error opening socket");

    if (::bind(sockFd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        this->socketError("Error binding socket");

    if (listen(sockFd, 100) < 0) this->socketError("Error binding socket");

    return sockFd;
}

struct sockaddr_in Server::getServerAddress(int port) {
    struct sockaddr_in serverAddress;
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    return serverAddress;
}

void Server::socketError(const char * msg, bool shouldThrow) {
    char err[500];
    sprintf(err, "%s: %s", msg, strerror(errno));
    this->logger.error(err);
    if (shouldThrow) {
        throw std::runtime_error(err);
    }
}







