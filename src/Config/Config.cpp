//
// Created by Oliver Johnstone on 25/04/2016.
//

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "Config.h"

using namespace boost::property_tree;

Config::Config(string configPath) {
    this->loadConfig(configPath);
}

void Config::loadConfig(string configPath) {
    ptree pt;
    ini_parser::read_ini(configPath, pt);

    try {

        this->properties["port"] = pt.get<string>("Server.port");
        this->properties["host"] = pt.get<string>("Server.host");
        this->properties["maxConnections"] = pt.get<string>("Server.maxConnections");
        this->properties["concurrentConnections"] = pt.get<string>("Server.concurrentConnections");

    } catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path>> e) {
        cout << "Invalid config file" << endl;
    }
}

string Config::getProperty(const char *propertyName) {
    return this->properties[propertyName];
}

int Config::getPort() {
    return stoi(this->getProperty("port"));
}

string Config::getHost() {
    return this->getProperty("host");
}

int Config::getMaxConnections() {
    return stoi(this->getProperty("maxConnections"));
}

int Config::getConcurrentConnections() {
    return stoi(this->getProperty("concurrentConnections"));
}