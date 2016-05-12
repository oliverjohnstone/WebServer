//
// Created by Oliver Johnstone on 12/05/2016.
//

#ifndef WEBSERVER_HOME_H
#define WEBSERVER_HOME_H

#include "../../HttpServer/Router/Route.h"

namespace Routes {
    namespace Home {
        class Home : public HttpServer::Router::Route {
        public:
            Home();
            void resolve(HttpServer::Request::Request &request, HttpServer::Response::Response &response);
        };
    }
}

#endif //WEBSERVER_HOME_H
