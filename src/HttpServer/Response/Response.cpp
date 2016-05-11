//
// Created by Oliver Johnstone on 10/05/2016.
//

#include "Response.h"

HttpServer::Response::Response::Response(HttpServer::Request::Request &request) : request(request) {
}

void HttpServer::Response::Response::setStatus(int status) {
}

void HttpServer::Response::Response::send(HttpServer::Connection *pConnection) {

}
