//
// Created by Oliver Johnstone on 10/05/2016.
//

#ifndef WEBSERVER_RESPONSE_H
#define WEBSERVER_RESPONSE_H

#include "../Connection.h"
#include "../Request/Request.h"

namespace HttpServer {
    namespace Response {

        class Response {
        public:

            Response(HttpServer::Request::Request &request);

            void setStatus(int status);

            void send(Connection *pConnection);

        private:
            HttpServer::Request::Request &request;
        };
    }
}


#endif //WEBSERVER_RESPONSE_H
