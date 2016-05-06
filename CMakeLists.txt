cmake_minimum_required(VERSION 3.5)
project(WebServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()

set (Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
set (Boost_USE_MULTITHREAD ON)  # enable multithreading
find_package (Boost COMPONENTS REQUIRED program_options system filesystem thread)

set(SOURCE_FILES main.cpp src/Config/Config.cpp src/Config/Config.h src/Config/ProgramOptions.cpp src/Config/ProgramOptions.h src/Logger/Logger.cpp src/Logger/Logger.h src/Server/Server.cpp src/Server/Server.h src/Server/ThreadPool/ThreadPool.cpp src/Server/ThreadPool/ThreadPool.h src/Server/ThreadPool/Task.cpp src/Server/ThreadPool/Task.h)
add_executable(WebServer ${SOURCE_FILES})
target_link_libraries (WebServer ${Boost_LIBRARIES})
