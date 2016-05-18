//
// Created by Oliver Johnstone on 11/05/2016.
//

#include "Router.h"

HttpServer::Router::Router::~Router() {
    for (std::vector<Route *>::iterator it = routes.begin(); it != routes.end(); ++it) {
        delete *it;
    }
}

void HttpServer::Router::Router::addRoute(Route *pRoute) {
    routes.push_back(pRoute);
}

void HttpServer::Router::Router::route(HttpServer::Request::Request &request, HttpServer::Response::Response &response) {
    for (std::vector<Route *>::iterator it = routes.begin(); it != routes.end(); ++it) {
        if ((*it)->canResolve(request)) {
            if ((*it)->resolve(request, response)) {
                break;
            }
        }
    }
}

void HttpServer::Router::Router::use(Middleware *pMiddleware) {
    routes.push_back(pMiddleware);
}



