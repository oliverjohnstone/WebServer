//
// Created by Oliver Johnstone on 11/05/2016.
//

#ifndef WEBSERVER_ROUTER_H
#define WEBSERVER_ROUTER_H

#include "Route.h"
#include <vector>

namespace HttpServer {
    namespace Router {
        class Router {
        public:
            ~Router();
            void addRoute(Route *pRoute);
            void route(HttpServer::Request::Request &request, HttpServer::Response::Response &response);

        private:
            std::vector<Route *> routes;
        };
    }
}


#endif //WEBSERVER_ROUTER_H
