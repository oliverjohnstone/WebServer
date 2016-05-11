//
// Created by Oliver Johnstone on 09/05/2016.
//
#include <boost/thread/lock_options.hpp>
#include "Request.h"

HttpServer::Request::Request::Request(HttpServer::Connection *pConnection) {
    this->pConnection = pConnection;
    if (!this->parseHeaders()) return;
    parseAccepts(this->accepts, "Accept");
    parseAccepts(this->encoding, "Accept-Encoding");
    parseAccepts(this->languages, "Accept-Language");
}

bool HttpServer::Request::Request::parseHeaders() {
    if (!this->parseRequestHeader(pConnection->readLine())) return false;
    do {
        string line = pConnection->readLine();
        if (line.empty()) return true;
        headers.addHeader(line);
    } while (!pConnection->isEof());
    return true;
}

bool HttpServer::Request::Request::parseRequestHeader(std::string header) {
    std::vector<std::string> requestParts, versionParts;

    boost::split(requestParts, header, boost::is_any_of("\t "));
    if (requestParts.size() != 3) {
//        response.setStatus(400);
//        response.send(pConnection);
        return false;
    }

    boost::split(versionParts, requestParts[2], boost::is_any_of("/"));

    if (versionParts.size() != 2) {
//        response.setStatus(400);
//        response.send(pConnection);
        return false;
    }

    request.method = requestParts[0];
    request.resource = requestParts[1];
    request.version = atof(versionParts[1].c_str());

    return true;
}

void HttpServer::Request::Request::parseAccepts(std::unordered_map<std::string, Accepts> &container, const char *header) {
    std::string acceptsHeader = headers.getHeader(header);
    if (!acceptsHeader.empty()) {
        std::vector<string> types;
        boost::algorithm::split(types, acceptsHeader, boost::is_any_of(","));

        for (std::vector<string>::iterator it = types.begin(); it != types.end(); ++it) {
            Accepts accept = parseAcceptParams(*it);
            container[accept.type] = accept;
        }
    }
}

HttpServer::Request::Accepts HttpServer::Request::Request::parseAcceptParams(std::string param) {
    HttpServer::Request::Accepts accept;

    accept.type = param;

    if (boost::algorithm::contains(param, ";")) {
        std::vector<string> params;
        boost::algorithm::split(params, param, boost::is_any_of(";"));
        if (params.size() > 0) {
            accept.type = params[0];
            std::vector<string>::iterator paramsIt = params.begin();
            // Ignore the first param which is actually the mime type
            paramsIt++;
            for (paramsIt; paramsIt != params.end(); ++paramsIt) {
                std::vector<string> paramQueries;
                boost::algorithm::split(paramQueries, *paramsIt, boost::is_any_of("="));
                boost::algorithm::trim(paramQueries[0]);

                if (paramQueries[0] == "q") {
                    accept.q = stod(paramQueries[1]);
                } else {
                    accept.params[paramQueries[0]] = paramQueries.size() == 2 ?
                                                     boost::algorithm::trim_copy(paramQueries[1]) :
                                                     NULL;
                }
            }
        }
    }

    return accept;
}

std::string &HttpServer::Request::Request::getResource() {
    return request.resource;
}

void HttpServer::Request::Request::setUrlParameter(std::string name, std::string value) {
    urlParameters[name] = value;
}

std::string HttpServer::Request::Request::getUrlParameter(std::string name) {
    try {
        return urlParameters[name];
    } catch (std::out_of_range &e) {
        return "";
    }
}

void HttpServer::Request::Request::clearUrlParameters() {
    urlParameters.clear();
}