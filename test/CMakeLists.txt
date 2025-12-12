cmake_minimum_required(VERSION 4.1)
project(test_bank_api)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(${PROJECT_NAME}
    ./main.cpp
    ../src/controller.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ../include
)

target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml2)