//
// Created by Oliver Johnstone on 28/04/2016.
//

#include "Server.h"
#include "../Routes/Home/Home.h"

using namespace HttpServer;

void Server::start() {
    bootRouter();
    socket = openSocket(config.getPort());

    threadPool = new ThreadPool::ThreadPool(config.getConcurrentConnections());

    while (running) {
        struct sockaddr_in clientAddress;
        socklen_t clientLength = sizeof(clientAddress);
        int clientSocket = accept(socket, (struct sockaddr *) &clientAddress, &clientLength);
        if (clientSocket < 0) socketError("Error opening client socket", false);

        Processor *processor = new Processor(logger, clientSocket, router);
        threadPool->addTask(processor);
    }
}

void Server::stop() {
    running = false;
    threadPool->stop();
    close(socket);
}

int Server::openSocket(int portNumber) {
    int sockFd;
    sockaddr_in serverAddress = getServerAddress(portNumber);

    sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) socketError("Error opening socket");

    if (::bind(sockFd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        this->socketError("Error binding socket");

    if (listen(sockFd, 100) < 0) socketError("Error binding socket");

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
    logger.error(err);
    if (shouldThrow) {
        throw std::runtime_error(err);
    }
}

void Server::bootRouter() {
    router.addRoute(new Routes::Home::Home());
}









