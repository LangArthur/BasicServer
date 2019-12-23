cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
project(BasicServer)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Adding valgrind flags
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-g)
endif()

set(CMAKE_CXX_FLAGS "-W -Wall -fprofile-arcs -ftest-coverage")

## Enable Google test library
enable_testing()

## Required packages
find_package(Threads)
find_package(GTest REQUIRED)

find_package(Boost 1.67 REQUIRED)

## General sources
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

## Server sources
set (SRC_SERVER
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TcpHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TcpSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UdpSocket.cpp
)

## Include headers to program
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

## Creating server executable
add_executable(BasicServer
    ${SRC}
    ${SRC_SERVER}
)

# set (SRC_TEST
# )

## Creating executable of unit tests
# include(GoogleTest)
# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../tests)
# add_executable(unit_tests
# )

target_link_libraries(BasicServer
    CONAN_PKG::boost_system
    CONAN_PKG::boost_asio
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
)

# target_link_libraries(unit_tests PUBLIC
#     CONAN_PKG::gtest
#     pthread
#     CONAN_PKG::boost_system
#     CONAN_PKG::boost_asio
#     ${CMAKE_THREAD_LIBS_INIT}
#     ${CMAKE_DL_LIBS}
# )