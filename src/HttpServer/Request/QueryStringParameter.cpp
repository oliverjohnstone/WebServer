//
// Created by Oliver Johnstone on 12/05/2016.
//

#include <cstdlib>
#include <boost/type_traits/is_same.hpp>
#include <boost/algorithm/string.hpp>
#include "QueryStringParameter.h"

HttpServer::Request::QueryStringParameter::QueryStringParameter(std::string paramName, std::string value) {
    parameterName = paramName;
    rawValue.push_back(value);
}

HttpServer::Request::QueryStringParameter::QueryStringParameter(std::string paramName, std::vector<std::string> value) : rawValue{value} {
    parameterName = paramName;
}

int HttpServer::Request::QueryStringParameter::getInt(int i) {
    return atoi(getString(i).c_str());
}

bool HttpServer::Request::QueryStringParameter::getBoolean(int i) {
    std::string lowercase = boost::algorithm::to_lower_copy(getString(i));
    return lowercase == "true" || lowercase == "1";
}

std::string HttpServer::Request::QueryStringParameter::getString(int i) {
    return rawValue[i];
}

double HttpServer::Request::QueryStringParameter::getDouble(int i) {
    return atof(getString(i).c_str());
}

std::string &HttpServer::Request::QueryStringParameter::getParamName() {
    return parameterName;
}

void HttpServer::Request::QueryStringParameter::push(std::string value) {
    rawValue.push_back(value);
}