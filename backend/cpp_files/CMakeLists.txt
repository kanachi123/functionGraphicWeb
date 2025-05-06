cmake_minimum_required(VERSION 3.10)
project(ComputeProject)

set(CMAKE_CXX_COMPILER "cl.exe")
set(CMAKE_C_COMPILER "cl.exe")

include_directories("D:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.29.30133/include")

set(NLOHMANN_JSON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/backend/cpp_files/nlohmann-json-v3.11.3/single_include")
include_directories(${NLOHMANN_JSON_INCLUDE_DIR})


set(MUPARSER_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/backend/cpp_files/muparser/include")
include_directories(${MUPARSER_INCLUDE_DIR})

set(SOURCES
    src/compute.cpp
)

add_executable(ComputeProject ${SOURCES})
