cmake_minimum_required(VERSION 3.16)

project(DataStructuresCPP LANGUAGES CXX)

# C++17 通用模板库 / C++17 generic template library.
add_library(data_structures INTERFACE)
target_compile_features(data_structures INTERFACE cxx_std_17)
target_include_directories(data_structures INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# 独立构建时默认启用检查；作为子项目时默认关闭。
# Enable the check by default for standalone builds, not for subprojects.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(DSCPP_STANDALONE ON)
else()
    set(DSCPP_STANDALONE OFF)
endif()

option(DSCPP_BUILD_CHECK "Build local data structure checks" ${DSCPP_STANDALONE})

if(DSCPP_BUILD_CHECK)
    # 在 build/ 目录生成检查程序，不新增 tests/ 等仓库目录。
    # Generate a local smoke test in the build tree, without adding source directories.
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dscpp_build_check.cpp" [=[
#include "sequential_list.h"
#include "singly_linked_list.h"
#include "circular_linked_list.h"
#include "doubly_linked_list.h"
#include "doubly_circular_linked_list.h"
#include "stack.h"
#include "queue.h"

#include <string>

template <typename List>
bool CheckList() {
    List list;
    int value = 0;

    if (!list.ListEmpty() || list.ListLength() != 0 ||
        list.GetElem(1, value) || list.ListDelete(1, value) ||
        list.ListInsert(0, 1)) {
        return false;
    }

    if (!list.ListInsert(1, 10) || !list.ListInsert(2, 30) ||
        !list.ListInsert(2, 20) || list.ListLength() != 3 ||
        !list.GetElem(2, value) || value != 20) {
        return false;
    }

    if (!list.ListDelete(2, value) || value != 20 ||
        list.ListLength() != 2 || !list.GetElem(2, value) || value != 30) {
        return false;
    }

    list.ClearList();
    return list.ListEmpty() && list.ListLength() == 0 &&
           list.ListInsert(1, 40) && list.GetElem(1, value) && value == 40;
}

template <typename List>
bool CheckLinkedLookup() {
    List list;
    int value = 0;

    if (!list.ListInsert(1, 10) || !list.ListInsert(2, 20) ||
        !list.ListInsert(3, 30) || list.LocateElem(20) != 2 ||
        list.LocateElem(99) != 0 || !list.PrevElem(20, value) || value != 10 ||
        !list.NextElem(20, value) || value != 30) {
        return false;
    }

    if (list.PrevElem(10, value) || list.NextElem(30, value) ||
        !list.PutElem(2, 25) || list.LocateElem(25) != 2) {
        return false;
    }

    return true;
}

bool CheckStack() {
    dscpp::Stack<int> stack;
    int value = 0;

    if (!stack.StackEmpty() || stack.Capacity() != 100 ||
        stack.Pop(value) || stack.GetTop(value)) {
        return false;
    }

    for (int i = 0; i < stack.Capacity(); i ++) {
        if (!stack.Push(i)) {
            return false;
        }
    }

    if (stack.Push(100) || stack.StackLength() != 100 ||
        !stack.GetTop(value) || value != 99) {
        return false;
    }

    for (int i = 99; i >= 0; i --) {
        if (!stack.Pop(value) || value != i) {
            return false;
        }
    }

    stack.ClearStack();
    return stack.StackEmpty() && stack.Push(7) &&
           stack.GetTop(value) && value == 7;
}

bool CheckQueue() {
    dscpp::Queue<int> queue(2);
    int value = 0;

    if (!queue.QueueEmpty() || queue.Capacity() != 2 ||
        queue.Dequeue(value) || queue.GetFront(value) ||
        !queue.Enqueue(1) || !queue.Enqueue(2) ||
        !queue.Dequeue(value) || value != 1 ||
        !queue.Enqueue(3) || !queue.Enqueue(4)) {
        return false;
    }

    if (queue.Capacity() != 4 || queue.QueueLength() != 3 ||
        !queue.GetFront(value) || value != 2) {
        return false;
    }

    for (int expected = 2; expected <= 4; expected ++) {
        if (!queue.Dequeue(value) || value != expected) {
            return false;
        }
    }

    dscpp::Queue<std::string> words(1);
    std::string word;
    return queue.QueueEmpty() && queue.Enqueue(9) &&
           queue.GetFront(value) && value == 9 &&
           words.Enqueue("hello") && words.Enqueue("world") &&
           words.Dequeue(word) && word == "hello" &&
           words.Dequeue(word) && word == "world";
}

int main() {
    if (!CheckList<dscpp::SequentialList<int>>()) return 1;
    if (!CheckList<dscpp::SinglyLinkedList<int>>()) return 2;
    if (!CheckList<dscpp::CircularLinkedList<int>>()) return 3;
    if (!CheckList<dscpp::DoublyLinkedList<int>>()) return 4;
    if (!CheckList<dscpp::DoublyCircularLinkedList<int>>()) return 5;

    if (!CheckLinkedLookup<dscpp::CircularLinkedList<int>>()) return 6;
    if (!CheckLinkedLookup<dscpp::DoublyLinkedList<int>>()) return 7;
    if (!CheckLinkedLookup<dscpp::DoublyCircularLinkedList<int>>()) return 8;

    if (!CheckStack()) return 9;
    if (!CheckQueue()) return 10;

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
