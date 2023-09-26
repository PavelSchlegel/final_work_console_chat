project(pass_lib LANGUAGE CXX)

set
(
    SOURCES
    optional_card.cpp
    optional_card.hpp
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