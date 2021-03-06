//
// Created by Oliver Johnstone on 12/05/2016.
//

#ifndef WEBSERVER_MIDDLEWARE_H
#define WEBSERVER_MIDDLEWARE_H

#include "../../Request/Request.h"
#include "../../Response/Response.h"
#include "../Route.h"

namespace HttpServer {
    namespace Router {
        class Middleware : public Route {
        public:
            Middleware() : Route("*") { }

            virtual bool resolve(HttpServer::Request::Request &request, HttpServer::Response::Response &response) = 0;
        };
    }
}

#endif //WEBSERVER_MIDDLEWARE_H
