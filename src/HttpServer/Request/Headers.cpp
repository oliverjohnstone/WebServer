//
// Created by Oliver Johnstone on 09/05/2016.
//

#include "Headers.h"
#include <boost/algorithm/string.hpp>
#include <vector>

#include <iostream>

bool HttpServer::Request::Headers::addHeader(std::string headerLine) {
    std::vector<std::string> headerParts;
    boost::algorithm::split(headerParts, headerLine, boost::is_any_of(":"));
    if (headerParts.size() != 2) return false;
    boost::algorithm::to_lower(headerParts[0]);
    boost::algorithm::trim(headerParts[1]);
    headers[headerParts[0]] = headerParts[1];
    return true;
}

void HttpServer::Request::Headers::addHeader(std::string headerName, std::string headerValue) {
    boost::algorithm::to_lower(headerName);
    boost::algorithm::trim(headerValue);
    headers[headerName] = headerValue;
}

std::string HttpServer::Request::Headers::getHeader(std::string headerName) {
    boost::algorithm::to_lower(headerName);
    try {
        return headers[headerName];
    } catch (std::out_of_range &e) {
        return "";
    }
}

