// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_SINGLY_LINKED_LIST_TEMPLATE_IMPL
#define DSCPP_SINGLY_LINKED_LIST_TEMPLATE_IMPL

#include "../include/singly_linked_list.h"

namespace dscpp {

// 创建空链表 / Create an empty list. Time: O(1).
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head = new SNode<T>;
    head -> next = nullptr;
    tail = head;
    size = 0;
}

// 释放全部结点 / Release all nodes. Time: O(n).
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    ClearList();
    delete head;
}

// 清空链表 / Clear the list. Time: O(n).
template <typename T>
void SinglyLinkedList<T>::ClearList() noexcept {
    SNode<T>* current = head -> next;

    while (current != nullptr) {
        SNode<T>* tmp = current;
        current = current -> next;
        delete tmp;
    }

    head -> next = nullptr;
    tail = head;
    size = 0;
}

// 判断是否为空 / Check whether empty. Time: O(1).
template <typename T>
bool SinglyLinkedList<T>::ListEmpty() const noexcept {
    return size == 0;
}

// 获取链表长度 / Get the list length. Time: O(1).
template <typename T>
int SinglyLinkedList<T>::ListLength() const noexcept {
    return size;
}

// 读取第 i 个元素 / Read element at position i. Time: O(n).
template <typename T>
bool SinglyLinkedList<T>::GetElem(int i, T& value) const {
    if (i < 1 || i > size) {
        return false;
    }

    SNode<T>* current = head -> next;

    for (int j = 1; j < i; j ++) {
        current = current -> next;
    }

    value = current -> data;
    return true;
}

// 在第 i 个位置插入 / Insert at position i. Time: O(n), O(1) at the tail.
template <typename T>
bool SinglyLinkedList<T>::ListInsert(int i, const T& value) {
    if (i < 1 || i - 1 > size) {
        return false;
    }

    SNode<T>* previous;

    if (i == size + 1) {
        previous = tail;
    } else {
        previous = head;

        for (int j = 1; j < i; j ++) {
            previous = previous -> next;
        }
    }

    SNode<T>* newNode = new SNode<T>{value, previous -> next};
    previous -> next = newNode;

    if (previous == tail) {
        tail = newNode;
    }

    size ++;
    return true;
}

// 删除第 i 个元素 / Delete element at position i. Time: O(n).
template <typename T>
bool SinglyLinkedList<T>::ListDelete(int i, T& deletedValue) {
    if (i < 1 || i > size) {
        return false;
    }

    SNode<T>* previous = head;

    for (int j = 1; j < i; j ++) {
        previous = previous -> next;
    }

    SNode<T>* target = previous -> next;
    deletedValue = target -> data;

    previous -> next = target -> next;

    if (target == tail) {
        tail = previous;
    }

    delete target;
    size --;
    return true;
}

}  // namespace dscpp

#endif  // DSCPP_SINGLY_LINKED_LIST_TEMPLATE_IMPL
