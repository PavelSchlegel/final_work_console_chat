cmake_minimum_required(VERSION 3.18)

include(FetchContent)
# FetchContent_Declare(
#     zlib
#     URL https://github.com/madler/zlib/releases/download/v1.3/zlib-1.3.tar.gz
#     OVERRIDE_FIND_PACKAGE
# )

# FetchContent_GetProperties(zlib)
# find_package(ZLIB REQUIRED)
# add_library(ZLIB::ZLIB ALIAS zlibstatic)
# target_include_directories(zlibstatic PUBLIC ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})

# set(BOOST_IOSTREAMS_ENABLE_ZLIB ON CACHE INTERNAL "")
FetchContent_Declare(
    boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.gz
)
FetchContent_MakeAvailable(boost)

add_subdirectory(src)

project(console_chat LANGUAGES CXX C VERSION 0.0.1)


add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

target_link_libraries(${PROJECT_NAME} PUBLIC Boost::headers chat)