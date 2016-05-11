//
// Created by Oliver Johnstone on 10/05/2016.
//

#ifndef WEBSERVER_RESPONSE_H
#define WEBSERVER_RESPONSE_H

#include "../Connection.h"

namespace HttpServer {
    namespace Response {
        class Response {
        public:

            void setStatus(int i);

            void send(HttpServer::Connection *pConnection);
        };
    }
}


#endif //WEBSERVER_RESPONSE_H
