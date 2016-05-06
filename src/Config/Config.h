//
// Created by Oliver Johnstone on 25/04/2016.
//

#ifndef WEBSERVER_CONFIG_H
#define WEBSERVER_CONFIG_H

#include <string>
#include <map>

using namespace std;

class Config {
public:
    Config(string configPath);
    int getPort();
    string getHost();
    int getMaxConnections();
    int getConcurrentConnections();

private:
    map<string, string> properties;

    string getProperty(const char *propertyName);
    void loadConfig(string configPath);
};


#endif //WEBSERVER_CONFIG_H
