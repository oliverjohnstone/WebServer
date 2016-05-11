//
// Created by Oliver Johnstone on 09/05/2016.
//

#ifndef WEBSERVER_REQUEST_H
#define WEBSERVER_REQUEST_H


#include "../Connection.h"
#include "Headers.h"
#include "../Response/Response.h"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <unordered_map>

namespace HttpServer {
    namespace Request {

        struct RequestLine {
            std::string method;
            std::string resource;
            double version;
        };

        struct Accepts {
            std::string type;
            double q;
            std::unordered_map<std::string, std::string> params;
        };

        class Request {
        public:
            Request(HttpServer::Connection *pConnection);

        private:
            HttpServer::Connection *pConnection;
            Headers headers;
            RequestLine request;
            Response::Response response;
            std::unordered_map<std::string, Accepts> accepts;
            std::unordered_map<std::string, Accepts> encoding;

            bool parseHeaders();
            bool parseRequestHeader(string header);
            void parseAccepts(std::unordered_map<std::string, Accepts> &container, const char *header);
            void parseLang();

            Accepts parseAcceptParams(std::string param);
        };
    }
}


#endif //WEBSERVER_REQUEST_H
