cmake_minimum_required(VERSION 4.1)
project(bank_api)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/controller.cpp
        test/main.cpp
)

if (MINGW)
    add_definitions(-D_WIN32_WINNT=0x0A00)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 mswsock)
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE
    ./include
)