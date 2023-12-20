cmake_minimum_required(VERSION 3.26)

project(hping_lite_v1
        VERSION 1
        DESCRIPTION ""
        LANGUAGES C)

set(CMAKE_C_STANDARD 17)

set(SANITIZE TRUE)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(SOURCE_LIST ${SOURCE_DIR}/main.c
        ${SOURCE_DIR}/fsm.c
        ${SOURCE_DIR}/hping.c
)
set(HEADER_LIST ${INCLUDE_DIR}
        ${INCLUDE_DIR}/fsm.h
        ${INCLUDE_DIR}/options.h
        ${INCLUDE_DIR}/hping.h
)
include_directories(${INCLUDE_DIR})

add_executable(hping_lite_v1 ${SOURCE_MAIN} ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(hping_lite_v1 PRIVATE include)
target_include_directories(hping_lite_v1 PRIVATE /usr/local/include)
target_link_directories(hping_lite_v1 PRIVATE /usr/local/lib)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_include_directories(hping_lite_v1 PRIVATE /usr/include)
endif ()

set_target_properties(hping_lite_v1 PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR})


# Add compiler flags
target_compile_options(hping_lite_v1 PRIVATE
        -Wall              # Enable all compiler warnings
        -Wextra            # Enable extra compiler warnings
        -pedantic          # Enable pedantic mode
        -O2                # Optimization level 2
        -g                 # Generate debug information
        -fPIC              # Generate position-independent code
        # Add more flags as needed
)

set_target_properties(hping_lite_v1 PROPERTIES OUTPUT_NAME "server")
install(TARGETS hping_lite_v1 DESTINATION bin)

