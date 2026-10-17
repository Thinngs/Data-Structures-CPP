// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_SEQUENTIAL_LIST_H
#define DSCPP_SEQUENTIAL_LIST_H

namespace dscpp {

// 顺序存储结构 / Sequential storage structure.
template <typename T>
struct SqList {
    T* elem = nullptr;
    int length = 0;
    int capacity = 0;
};

// 通用顺序表（位序从 1 开始）/ Generic sequential list (1-based positions).
template <typename T>
class SequentialList {
private:
    static constexpr int kInitialCapacity = 4;
    static constexpr int kCapacityIncrement = 4;

    SqList<T> list;

    // 扩大容量 / Expand capacity. Time: O(n).
    void Expand();

public:
    // 创建空表 / Create an empty list. Time: O(1).
    SequentialList();

    // 释放存储空间 / Release storage. Time: O(capacity).
    ~SequentialList();

    SequentialList(const SequentialList&) = delete;
    SequentialList& operator=(const SequentialList&) = delete;

    // 逻辑清空（保留容量）/ Clear logically (retain capacity). Time: O(1).
    void ClearList() noexcept;

    // 判断是否为空 / Check whether empty. Time: O(1).
    bool ListEmpty() const noexcept;

    // 获取长度 / Get length. Time: O(1).
    int ListLength() const noexcept;

    // 获取容量 / Get capacity. Time: O(1).
    int Capacity() const noexcept;

    // 读取第 i 个元素 / Read element at position i. Time: O(1).
    bool GetElem(int i, T& value) const;

    // 修改第 i 个元素 / Replace element at position i. Time: O(1).
    bool PutElem(int i, const T& value);

    // 在第 i 个位置插入 / Insert at position i. Time: O(n).
    bool ListInsert(int i, const T& value);

    // 删除第 i 个元素 / Delete element at position i. Time: O(n).
    bool ListDelete(int i, T& deletedValue);
};

}  // namespace dscpp

// 模板定义必须可见 / Template definitions must be visible to callers.
#include "../src/sequential_list.cpp"

#endif  // DSCPP_SEQUENTIAL_LIST_H
