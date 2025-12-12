cmake_minimum_required(VERSION 4.1)
project(bank_api)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(./libs/drogon)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
)
