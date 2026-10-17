// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_SEQUENTIAL_LIST_TEMPLATE_IMPL
#define DSCPP_SEQUENTIAL_LIST_TEMPLATE_IMPL

#include "../include/sequential_list.h"

#include <limits>
#include <stdexcept>

namespace dscpp {

// 创建空表 / Create an empty list. Time: O(1).
template <typename T>
SequentialList<T>::SequentialList() {
    list.elem = new T[kInitialCapacity];
    list.capacity = kInitialCapacity;
}

// 释放存储空间 / Release storage. Time: O(capacity).
template <typename T>
SequentialList<T>::~SequentialList() {
    delete[] list.elem;
}

// 扩大容量 / Expand capacity. Time: O(n).
template <typename T>
void SequentialList<T>::Expand() {
    if (list.capacity > std::numeric_limits<int>::max() - kCapacityIncrement) {
        throw std::length_error("SequentialList capacity overflow");
    }

    int newCapacity = list.capacity + kCapacityIncrement;
    T* newElem = new T[newCapacity];

    try {
        for (int i = 0; i < list.length; i ++) {
            newElem[i] = list.elem[i];
        }
    } catch (...) {
        delete[] newElem;
        throw;
    }

    delete[] list.elem;
    list.elem = newElem;
    list.capacity = newCapacity;
}

// 逻辑清空（保留容量）/ Clear logically (retain capacity). Time: O(1).
template <typename T>
void SequentialList<T>::ClearList() noexcept {
    list.length = 0;
}

// 判断是否为空 / Check whether empty. Time: O(1).
template <typename T>
bool SequentialList<T>::ListEmpty() const noexcept {
    return list.length == 0;
}

// 获取长度 / Get length. Time: O(1).
template <typename T>
int SequentialList<T>::ListLength() const noexcept {
    return list.length;
}

// 获取容量 / Get capacity. Time: O(1).
template <typename T>
int SequentialList<T>::Capacity() const noexcept {
    return list.capacity;
}

// 读取第 i 个元素 / Read element at position i. Time: O(1).
template <typename T>
bool SequentialList<T>::GetElem(int i, T& value) const {
    if (i < 1 || i > list.length) {
        return false;
    }

    value = list.elem[i - 1];
    return true;
}

// 修改第 i 个元素 / Replace element at position i. Time: O(1).
template <typename T>
bool SequentialList<T>::PutElem(int i, const T& value) {
    if (i < 1 || i > list.length) {
        return false;
    }

    list.elem[i - 1] = value;
    return true;
}

// 在第 i 个位置插入 / Insert at position i. Time: O(n).
template <typename T>
bool SequentialList<T>::ListInsert(int i, const T& value) {
    if (i < 1 || i - 1 > list.length) {
        return false;
    }

    // 提前复制，避免 value 引用表内元素时被移动 / Copy before shifting.
    T insertedValue = value;

    if (list.length == list.capacity) {
        Expand();
    }

    for (int j = list.length; j >= i; j --) {
        list.elem[j] = list.elem[j - 1];
    }

    list.elem[i - 1] = insertedValue;
    list.length ++;

    return true;
}

// 删除第 i 个元素 / Delete element at position i. Time: O(n).
template <typename T>
bool SequentialList<T>::ListDelete(int i, T& deletedValue) {
    if (i < 1 || i > list.length) {
        return false;
    }

    deletedValue = list.elem[i - 1];

    for (int j = i; j < list.length; j ++) {
        list.elem[j - 1] = list.elem[j];
    }

    list.length --;
    return true;
}

}  // namespace dscpp

#endif  // DSCPP_SEQUENTIAL_LIST_TEMPLATE_IMPL
