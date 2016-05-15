//
// Created by Oliver Johnstone on 12/05/2016.
//

#ifndef WEBSERVER_QUERYSTRING_H
#define WEBSERVER_QUERYSTRING_H


#include "../../Router/Middleware/Middleware.h"

namespace HttpServer {
    namespace Middleware {
        namespace BodyParser {
            class QueryString : public HttpServer::Router::Middleware {
                void resolve(HttpServer::Request::Request &request, HttpServer::Response::Response &response);
                void push(std::string value);
                std::vector<HttpServer::Request::QueryStringParameter *> & parseParams(std::vector<std::string> &params);
            };
        }
    }
}



#endif //WEBSERVER_QUERYSTRING_H
