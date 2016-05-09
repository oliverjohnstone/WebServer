//
// Created by Oliver Johnstone on 09/05/2016.
//

#ifndef WEBSERVER_REQUEST_H
#define WEBSERVER_REQUEST_H


#include "../Connection.h"

namespace HttpServer {
    namespace Request {
        class Request {
        public:
            Request(HttpServer::Connection *pConnection);

        private:
            HttpServer::Connection *pConnection;

        };
    }
}


#endif //WEBSERVER_REQUEST_H
