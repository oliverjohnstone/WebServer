//
// Created by Oliver Johnstone on 09/05/2016.
//

#ifndef WEBSERVER_HEADERS_H
#define WEBSERVER_HEADERS_H

#include <unordered_map>
#include <string>

namespace HttpServer {
    namespace Request {
        class Headers {
        public:
            bool addHeader(std::string headerLine);
            void addHeader(std::string headerName, std::string headerValue);
            std::string getHeader(std::string headerName);
        private:
            std::unordered_map<std::string, std::string> headers;
        };
    }
}

#endif //WEBSERVER_HEADERS_H
