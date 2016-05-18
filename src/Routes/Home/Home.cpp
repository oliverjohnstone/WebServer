//
// Created by Oliver Johnstone on 12/05/2016.
//

#include "Home.h"
#include <iostream>

Routes::Home::Home::Home() : Route("/") {
}

bool Routes::Home::Home::resolve(HttpServer::Request::Request &request, HttpServer::Response::Response &response) {
    std::cout << "Home Page" << std::endl;
    return true;
}