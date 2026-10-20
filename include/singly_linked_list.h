// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_SINGLY_LINKED_LIST_H
#define DSCPP_SINGLY_LINKED_LIST_H

namespace dscpp {

// 单链表结点 / Singly linked list node.
template <typename T>
struct SNode {
    T data;
    SNode<T>* next = nullptr;
};

// 带头结点的通用单链表（位序从 1 开始）/ Generic singly linked list with a dummy head (1-based positions).
// T 需支持默认构造、复制构造和复制赋值 / T must be default-constructible, copy-constructible, and copy-assignable.
template <typename T>
class SinglyLinkedList {
private:
    SNode<T>* head = nullptr;
    SNode<T>* tail = nullptr;
    int size = 0;

public:
    // 创建空链表 / Create an empty list. Time: O(1).
    SinglyLinkedList();

    // 释放全部结点 / Release all nodes. Time: O(n).
    ~SinglyLinkedList();

    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    // 清空链表 / Clear the list. Time: O(n).
    void ClearList() noexcept;

    // 判断是否为空 / Check whether empty. Time: O(1).
    bool ListEmpty() const noexcept;

    // 获取链表长度 / Get the list length. Time: O(1).
    int ListLength() const noexcept;

    // 读取第 i 个元素 / Read element at position i. Time: O(n).
    bool GetElem(int i, T& value) const;

    // 在第 i 个位置插入 / Insert at position i. Time: O(n), O(1) at the tail.
    bool ListInsert(int i, const T& value);

    // 删除第 i 个元素 / Delete element at position i. Time: O(n).
    bool ListDelete(int i, T& deletedValue);
};

}  // namespace dscpp

// 模板定义必须可见 / Template definitions must be visible to callers.
#include "../src/singly_linked_list.cpp"

#endif  // DSCPP_SINGLY_LINKED_LIST_H
