cmake_minimum_required(VERSION 4.1)
project(bank_api VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(bank_api__BUILD_TESTS ON)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/controller.cpp
)


add_subdirectory(libs/tinyxml2)
if (MINGW)
    if (WIN32)
        add_definitions(-D_WIN32_WINNT=0x0A00)
    endif ()

    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 mswsock)
endif ()


if (bank_api__BUILD_TESTS)
    add_subdirectory(./test test_bank_api)
endif ()


target_include_directories(${PROJECT_NAME} PRIVATE
    ./include
)
target_link_libraries(${PROJECT_NAME} PRIVATE tinyxml2)