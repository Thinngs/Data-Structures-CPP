cmake_minimum_required(VERSION 3.16)

project(DataStructuresCPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 头文件模板库 / Header-based template library.
add_library(data_structures INTERFACE)
target_include_directories(data_structures INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_compile_features(data_structures INTERFACE cxx_std_17)

# 仅独立构建仓库时默认测试 / Enable check by default only for standalone builds.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(DSCPP_STANDALONE ON)
else()
    set(DSCPP_STANDALONE OFF)
endif()

option(DSCPP_BUILD_CHECK "Build local data structure checks" ${DSCPP_STANDALONE})

if(DSCPP_BUILD_CHECK)
    # 测试代码生成于 build/，无需提交 / Generate test source inside build/.
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dscpp_build_check.cpp" [=[
#include "sequential_list.h"
#include "singly_linked_list.h"

#include <string>

int main() {
    dscpp::SequentialList<int> numbers;
    if (!numbers.ListInsert(1, 10) || !numbers.ListInsert(2, 20)) {
        return 1;
    }

    int value = 0;
    if (!numbers.GetElem(2, value) || value != 20) {
        return 2;
    }

    if (!numbers.ListDelete(1, value) || value != 10) {
        return 3;
    }

    dscpp::SinglyLinkedList<int> linked;
    if (!linked.ListInsert(1, 10) || !linked.ListInsert(2, 20)) {
        return 4;
    }

    if (!linked.ListInsert(2, 15) || !linked.GetElem(2, value) || value != 15) {
        return 5;
    }

    if (!linked.ListDelete(3, value) || value != 20) {
        return 6;
    }

    linked.ClearList();
    if (!linked.ListEmpty() || !linked.ListInsert(1, 99)) {
        return 7;
    }

    dscpp::SinglyLinkedList<std::string> words;
    if (!words.ListInsert(1, "hello")) {
        return 8;
    }

    std::string word;
    if (!words.GetElem(1, word) || word != "hello") {
        return 9;
    }

    return 0;
}
]=])

    add_executable(dscpp_build_check
        "${CMAKE_CURRENT_BINARY_DIR}/dscpp_build_check.cpp"
    )
    target_link_libraries(dscpp_build_check PRIVATE data_structures)

    enable_testing()
    add_test(NAME data_structures_check COMMAND dscpp_build_check)
endif()
