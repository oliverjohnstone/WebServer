//
// Created by Oliver Johnstone on 11/05/2016.
//

#ifndef WEBSERVER_ROUTE_H
#define WEBSERVER_ROUTE_H

#include "../Request/Request.h"
#include "../Response/Response.h"
#include <string>

namespace HttpServer {
    namespace Router {
        class Route {
        public:
            Route(std::string routeMatch);
            virtual void resolve(HttpServer::Request::Request &request, HttpServer::Response::Response &response) = 0;
            bool canResolve(HttpServer::Request::Request &request);

        private:
            std::string routeMatch;
        };
    }
}



#endif //WEBSERVER_ROUTE_H
