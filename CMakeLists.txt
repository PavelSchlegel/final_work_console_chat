cmake_minimum_required(VERSION 3.18)

include(FetchContent)

FetchContent_Declare(
    boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.gz
)
FetchContent_MakeAvailable(boost)

include(FetchContent)
enable_testing()

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)

project(chat LANGUAGES CXX C VERSION 0.0.1)


add_executable(${PROJECT_NAME}-server server.cpp)
target_link_libraries(${PROJECT_NAME}-server PUBLIC chat)

set_target_properties(${PROJECT_NAME}-server
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

add_executable(${PROJECT_NAME}-client client.cpp)
target_link_libraries(${PROJECT_NAME}-client PUBLIC chat)

set_target_properties(${PROJECT_NAME}-client
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)
