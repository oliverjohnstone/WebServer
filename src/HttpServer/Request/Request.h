//
// Created by Oliver Johnstone on 09/05/2016.
//

#ifndef WEBSERVER_REQUEST_H
#define WEBSERVER_REQUEST_H


#include "../Connection.h"
#include "Headers.h"
#include "QueryStringParameter.h"
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
            ~Request();
            std::string & getResource();
            void setQueryParameter(HttpServer::Request::QueryStringParameter *param);
            void setUrlParameter(std::string name, std::string value);
            HttpServer::Request::QueryStringParameter * getUrlParameter(std::string name);
            void clearUrlParameters();
            void clearQueryStringParameters();

        private:
            HttpServer::Connection *pConnection;
            Headers headers;
            RequestLine request;
            std::unordered_map<std::string, Accepts> accepts;
            std::unordered_map<std::string, Accepts> encoding;
            std::unordered_map<std::string, Accepts> languages;
            std::unordered_map<std::string, QueryStringParameter *> queryStringParameters;
            std::unordered_map<std::string, std::string> urlParameters;

            bool parseHeaders();
            bool parseRequestHeader(string header);
            void parseAccepts(std::unordered_map<std::string, Accepts> &container, const char *header);
            Accepts parseAcceptParams(std::string param);
        };
    }
}

#endif //WEBSERVER_REQUEST_H
