//
// Created by Oliver Johnstone on 12/05/2016.
//

#include "QueryString.h"

void HttpServer::Middleware::BodyParser::QueryString::resolve(HttpServer::Request::Request &request,
                                                              HttpServer::Response::Response &response) {
    std::string resource = request.getResource();
    if (boost::algorithm::contains(resource, "?")) {
        std::vector<std::string> parts;
        boost::algorithm::split(parts, resource, boost::is_any_of("?"));
        if (parts.size() >= 2) {
            std::vector<std::string> urlParams;
            boost::algorithm::split(parts, resource, boost::is_any_of("&"));

            std::vector<HttpServer::Request::QueryStringParameter *> parsedParams = parseParams(urlParams);
            for (std::vector<HttpServer::Request::QueryStringParameter *>::iterator it = parsedParams.begin(); it != parsedParams.end(); ++it) {
                request.setQueryParameter((*it));
            }
        }
    }
}

std::vector<HttpServer::Request::QueryStringParameter *> & HttpServer::Middleware::BodyParser::QueryString::parseParams(
        std::vector<std::string> &params) {

    std::vector<HttpServer::Request::QueryStringParameter *> parsed;

    for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); ++it) {
        std::string value = "true";
        std::string name = (*it);
        auto i = (*it).find_first_of('=');
        if (i != std::string::npos) {
            name = (*it).substr(0, i);
            value = (*it).substr(i + 1);
        }

        if (boost::algorithm::ends_with(name, "[]")) {
            name = name.substr(0, name.find_last_of("[]"));
            HttpServer::Request::QueryStringParameter * found = nullptr;
            for (std::vector<HttpServer::Request::QueryStringParameter *>::iterator qIt = parsed.begin(); qIt != parsed.end(); ++qIt) {
                if ((*qIt)->getParamName() == name) {
                    found = (*qIt);
                    break;
                }
            }

            if (found == nullptr) {
                parsed.push_back(new HttpServer::Request::QueryStringParameter(name, value));
            } else {
                found->push(value);
            }
        } else {
            parsed.push_back(new HttpServer::Request::QueryStringParameter(name, value));
        }
    }

    return parsed;
}



