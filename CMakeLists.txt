cmake_minimum_required(VERSION 3.16)

project(DataStructuresCPP
    VERSION 1.0.0
    LANGUAGES CXX
)

# Use C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build the existing data structure implementations as a static library.
add_library(dscpp STATIC
    src/circular_linked_list.cpp
    src/doubly_circular_linked_list.cpp
    src/doubly_linked_list.cpp
    src/hstring.cpp
    src/istring.cpp
    src/queue.cpp
    src/singly_linked_list.cpp
    src/sstring.cpp
    src/stack.cpp
)

# Public alias for consumers.
add_library(dscpp::dscpp ALIAS dscpp)

# Expose the public headers in include/.
target_include_directories(dscpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(dscpp PUBLIC cxx_std_17)

set_target_properties(dscpp PROPERTIES
    OUTPUT_NAME "dscpp"
    CXX_EXTENSIONS OFF
)

# Enable common compiler warnings.
if(MSVC)
    target_compile_options(dscpp PRIVATE /W4)
else()
    target_compile_options(dscpp PRIVATE -Wall -Wextra -Wpedantic)
endif()

# sequential_list.cpp is included by sequential_list.h because it contains
# template definitions. Do not compile it as a separate source file here.
