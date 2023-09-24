project(pass_lib LANGUAGE CXX)

set
(
    SOURCES
    pass_processing.cpp
    pass_processing.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties
(
    ${PROJECT_NAME}
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)