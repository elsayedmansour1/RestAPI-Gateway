cmake_minimum_required(VERSION 3.5)
project(RestApiGateway)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core DBus Network REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    DBusManager.cpp
    DBusManager.h
    HttpServer.cpp
    HttpServer.h
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::DBus
    Qt5::Network
)