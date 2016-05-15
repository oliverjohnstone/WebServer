cmake_minimum_required(VERSION 3.5)
project(WebServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()

set (Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
set (Boost_USE_MULTITHREAD ON)  # enable multithreading
find_package (Boost COMPONENTS REQUIRED program_options system filesystem thread regex)

set(SOURCE_FILES main.cpp src/Config/Config.cpp src/Config/Config.h src/Config/ProgramOptions.cpp src/Config/ProgramOptions.h src/Logger/Logger.cpp src/Logger/Logger.h src/HttpServer/Server.cpp src/HttpServer/Server.h src/HttpServer/ThreadPool/ThreadPool.cpp src/HttpServer/ThreadPool/ThreadPool.h src/HttpServer/ThreadPool/Task.cpp src/HttpServer/ThreadPool/Task.h src/HttpServer/Processor.cpp src/HttpServer/Processor.h src/HttpServer/Connection.cpp src/HttpServer/Connection.h src/HttpServer/Request/Request.cpp src/HttpServer/Request/Request.h src/HttpServer/Request/Headers.cpp src/HttpServer/Request/Headers.h src/HttpServer/Response/Response.cpp src/HttpServer/Response/Response.h src/HttpServer/Router/Router.cpp src/HttpServer/Router/Router.h src/HttpServer/Router/Route.cpp src/HttpServer/Router/Route.h src/Routes/Home/Home.cpp src/Routes/Home/Home.h src/HttpServer/Router/Middleware/Middleware.h src/HttpServer/Middleware/BodyParser/QueryString.cpp src/HttpServer/Middleware/BodyParser/QueryString.h src/HttpServer/Request/QueryStringParameter.cpp src/HttpServer/Request/QueryStringParameter.h)
add_executable(WebServer ${SOURCE_FILES})
target_link_libraries (WebServer ${Boost_LIBRARIES})
