cmake_minimum_required(VERSION 3.16)

project(DataStructuresCPP LANGUAGES CXX)

option(DSCPP_BUILD_TESTS "Build tests" ON)

# The target is interface-only until the first .cpp implementation is added.
add_library(data_structures INTERFACE)
add_library(DataStructuresCPP::data_structures ALIAS data_structures)

target_compile_features(data_structures INTERFACE cxx_std_17)
target_include_directories(data_structures INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(DSCPP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
