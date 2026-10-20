// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_DOUBLY_LINKED_LIST_H
#define DSCPP_DOUBLY_LINKED_LIST_H

namespace dscpp {

// 双链表结点 / Doubly linked list node.
template <typename T>
struct DLNode {
    T data;
    DLNode<T>* prior = nullptr;
    DLNode<T>* next = nullptr;
};

// 带头结点的通用非循环双链表（位序从 1 开始）/ Generic non-circular doubly linked list with a dummy head (1-based positions).
// T 需支持默认构造、复制构造和复制赋值；按值查找还需支持 ==。
// T must support default construction, copy construction, and copy assignment; value searches also require ==.
template <typename T>
class DoublyLinkedList {
private:
    DLNode<T>* head = nullptr;
    DLNode<T>* tail = nullptr;
    int size = 0;

    // 从较近的一端查找第 i 个结点 / Find node i from the nearer end. Time: O(n).
    DLNode<T>* GetNode(int i) const noexcept;

public:
    // 创建空双链表 / Create an empty doubly linked list. Time: O(1).
    DoublyLinkedList();

    // 释放全部结点 / Release all nodes. Time: O(n).
    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    // 清空链表 / Clear the list. Time: O(n).
    void ClearList() noexcept;

    // 判断是否为空 / Check whether empty. Time: O(1).
    bool ListEmpty() const noexcept;

    // 获取链表长度 / Get the list length. Time: O(1).
    int ListLength() const noexcept;

    // 读取第 i 个元素 / Read element at position i. Time: O(n).
    bool GetElem(int i, T& value) const;

    // 修改第 i 个元素 / Replace element at position i. Time: O(n).
    bool PutElem(int i, const T& value);

    // 查找元素首次出现的位序（未找到返回 0）/ Find the first position of a value (0 if absent). Time: O(n).
    int LocateElem(const T& value) const;

    // 获取首次匹配元素的前驱 / Get the predecessor of the first matching element. Time: O(n).
    bool PrevElem(const T& value, T& previousValue) const;

    // 获取首次匹配元素的后继 / Get the successor of the first matching element. Time: O(n).
    bool NextElem(const T& value, T& nextValue) const;

    // 在第 i 个位置插入 / Insert at position i. Time: O(n), O(1) at either end.
    bool ListInsert(int i, const T& value);

    // 删除第 i 个元素 / Delete element at position i. Time: O(n), O(1) at either end.
    bool ListDelete(int i, T& deletedValue);
};

}  // namespace dscpp

// 模板定义必须可见 / Template definitions must be visible to callers.
#include "../src/doubly_linked_list.cpp"

#endif  // DSCPP_DOUBLY_LINKED_LIST_H
