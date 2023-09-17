project(chat LANGUAGES CXX C)

add_library(${PROJECT_NAME} STATIC server.cpp function.cpp)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)

target_link_libraries(${PROJECT_NAME} PUBLIC Boost::lexical_cast)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME}-test test.cpp)
target_link_libraries(${PROJECT_NAME}-test PUBLIC ${PROJECT_NAME} gtest_main gmock gtest)
add_test(NAME ${PROJECT_NAME}-test COMMAND ${PROJECT_NAME}-test)