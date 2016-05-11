//
// Created by Oliver Johnstone on 11/05/2016.
//

#include "Route.h"
#include <boost/algorithm/string_regex.hpp>

HttpServer::Router::Route::Route(std::string routeMatch) {
    this->routeMatch = routeMatch;
}

bool HttpServer::Router::Route::canResolve(HttpServer::Request::Request &request) {
    std::string &resource = request.getResource();

    if (routeMatch == "*") return true;
    if (routeMatch == resource) return true;

    std::vector<std::string> urlParts;
    std::vector<std::string> names;
    std::string regexExp;

    boost::algorithm::split(urlParts, resource, boost::is_any_of("/"));
    for (std::vector<string>::iterator it = urlParts.begin(); it != urlParts.end(); ++it) {
        if (boost::algorithm::starts_with(*it, ":")) {
            regexExp += "/(\\w*)";
            names.push_back(*it);
        } else {
            regexExp += "/" + *it;
        }
    }

    boost::regex expression(regexExp);
    boost::cmatch match;
    if (boost::regex_match(resource.c_str(), match, expression)) {
        for (int i = 1; i < match.size(); i++) {
            if (names.size() < i) {
                request.setUrlParameter(names[i], match[i]);
            } else {
                request.clearUrlParameters();
                return false;
            }
        }

        return true;
    }

    return false;
}