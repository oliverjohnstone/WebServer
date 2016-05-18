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
    std::string qs = "";

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

    unsigned long qsPos = requestParts[1].find_first_of('?');
    if (qsPos != std::string::npos) {
        qs = requestParts[1].substr(qsPos + 1);
        requestParts[1] = requestParts[1].substr(0, qsPos);
    }

    request.method = requestParts[0];
    request.resource = requestParts[1];
    request.queryString = qs;
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

void HttpServer::Request::Request::setQueryParameter(HttpServer::Request::QueryStringParameter *param) {
    queryStringParameters[param->getParamName()] = param;
}

HttpServer::Request::QueryStringParameter *HttpServer::Request::Request::getUrlParameter(std::string name) {
    try {
        return queryStringParameters[name];
    } catch (std::out_of_range &e) {
        return nullptr;
    }
}

void HttpServer::Request::Request::clearUrlParameters() {
    urlParameters.clear();
}

HttpServer::Request::Request::~Request() {
    clearUrlParameters();
    clearQueryStringParameters();
}

void HttpServer::Request::Request::setUrlParameter(std::string name, std::string value) {
    urlParameters[name] = value;
}

void HttpServer::Request::Request::clearQueryStringParameters() {
    for (std::unordered_map<std::string, QueryStringParameter *>::iterator it = queryStringParameters.begin();
         it != queryStringParameters.end(); ++it) {

        delete (*it).second;
    }
    queryStringParameters.clear();
}

std::string &HttpServer::Request::Request::getQueryString() {
    return request.queryString;
}