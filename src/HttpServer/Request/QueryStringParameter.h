//
// Created by Oliver Johnstone on 12/05/2016.
//

#ifndef WEBSERVER_QUERYSTRINGPARAMETER_H
#define WEBSERVER_QUERYSTRINGPARAMETER_H

#include <string>
#include <vector>

namespace HttpServer {
    namespace Request {

        class QueryStringParameter {
        public:
            QueryStringParameter(std::string paramName, std::string value);
            QueryStringParameter(std::string paramName, std::vector<std::string> value);

            std::string &getParamName();
            void push(std::string value);

            int getInt(int i = 0);
            bool getBoolean(int i = 0);
            std::string getString(int i = 0);
            double getDouble(int i = 0);

        private:
            std::string parameterName;
            std::vector<std::string> rawValue;
        };
    }
}

#endif //WEBSERVER_QUERYSTRINGPARAMETER_H
