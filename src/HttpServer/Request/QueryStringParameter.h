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

            template<typename T> T get(int i = 0);
            std::string &getParamName();
            void push(std::string value);
        private:
            std::string parameterName;
            std::vector<std::string> rawValue;

            int getInt(int i);
            bool getBoolean(int i);
            std::string getString(int i);
            double getDouble(int i);
        };
    }
}

#endif //WEBSERVER_QUERYSTRINGPARAMETER_H
