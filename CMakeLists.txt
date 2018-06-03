cmake_minimum_required(VERSION 2.8)

if (NOT UNIX)
    message (FATAL_ERROR "Not Unix!")
endif ()

project(crypt)

set(CRYPTOPP_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)

include_directories(${CMAKE_SOURCE_DIR}/lib/include/)
link_directories(${CRYPTOPP_LIB_DIR}/)

file(GLOB HEADERS "${SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

find_library(CRYPT libcryptopp.so.7 ${CRYPTOPP_LIB_DIR})

message("\nCheckings libraries ..." )
message(STATUS "cryptopp: " ${CRYPT})
message("")

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall")

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(run ${SOURCES} ${HEADERS})

message(STATUS ${CRYPT})

target_link_libraries(run ${CRYPT})
