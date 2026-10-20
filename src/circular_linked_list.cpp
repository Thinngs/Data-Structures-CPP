// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_CIRCULAR_LINKED_LIST_TEMPLATE_IMPL
#define DSCPP_CIRCULAR_LINKED_LIST_TEMPLATE_IMPL

#include "../include/circular_linked_list.h"

namespace dscpp {

// 创建空循环链表 / Create an empty circular list. Time: O(1).
template <typename T>
CircularLinkedList<T>::CircularLinkedList() {
    head = new CNode<T>;
    head -> next = head;
    tail = head;
    size = 0;
}

// 释放全部结点 / Release all nodes. Time: O(n).
template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
    ClearList();
    delete head;
}

// 清空链表 / Clear the list. Time: O(n).
template <typename T>
void CircularLinkedList<T>::ClearList() noexcept {
    CNode<T>* current = head -> next;

    while (current != head) {
        CNode<T>* tmp = current;
        current = current -> next;
        delete tmp;
    }

    head -> next = head;
    tail = head;
    size = 0;
}

// 判断是否为空 / Check whether empty. Time: O(1).
template <typename T>
bool CircularLinkedList<T>::ListEmpty() const noexcept {
    return size == 0;
}

// 获取链表长度 / Get the list length. Time: O(1).
template <typename T>
int CircularLinkedList<T>::ListLength() const noexcept {
    return size;
}

// 读取第 i 个元素 / Read element at position i. Time: O(n).
template <typename T>
bool CircularLinkedList<T>::GetElem(int i, T& value) const {
    if (i < 1 || i > size) {
        return false;
    }

    CNode<T>* current = head -> next;

    for (int j = 1; j < i; j ++) {
        current = current -> next;
    }

    value = current -> data;
    return true;
}

// 修改第 i 个元素 / Replace element at position i. Time: O(n).
template <typename T>
bool CircularLinkedList<T>::PutElem(int i, const T& value) {
    if (i < 1 || i > size) {
        return false;
    }

    CNode<T>* current = head -> next;

    for (int j = 1; j < i; j ++) {
        current = current -> next;
    }

    current -> data = value;
    return true;
}

// 查找元素首次出现的位序（未找到返回 0）/ Find the first position of a value (0 if absent). Time: O(n).
template <typename T>
int CircularLinkedList<T>::LocateElem(const T& value) const {
    CNode<T>* current = head -> next;

    for (int i = 1; i <= size; i ++) {
        if (current -> data == value) {
            return i;
        }

        current = current -> next;
    }

    return 0;
}

// 获取首次匹配元素的前驱 / Get the predecessor of the first matching element. Time: O(n).
template <typename T>
bool CircularLinkedList<T>::PrevElem(const T& value, T& previousValue) const {
    CNode<T>* previousNode = head;
    CNode<T>* current = head -> next;

    for (int i = 1; i <= size; i ++) {
        if (current -> data == value) {
            if (previousNode == head) {
                return false;
            }

            previousValue = previousNode -> data;
            return true;
        }

        previousNode = current;
        current = current -> next;
    }

    return false;
}

// 获取首次匹配元素的后继 / Get the successor of the first matching element. Time: O(n).
template <typename T>
bool CircularLinkedList<T>::NextElem(const T& value, T& nextValue) const {
    CNode<T>* current = head -> next;

    for (int i = 1; i <= size; i ++) {
        if (current -> data == value) {
            if (i == size) {
                return false;
            }

            nextValue = current -> next -> data;
            return true;
        }

        current = current -> next;
    }

    return false;
}

// 在第 i 个位置插入 / Insert at position i. Time: O(n), O(1) at the tail.
template <typename T>
bool CircularLinkedList<T>::ListInsert(int i, const T& value) {
    if (i < 1 || i - 1 > size) {
        return false;
    }

    CNode<T>* previous;

    if (i - 1 == size) {
        previous = tail;
    } else {
        previous = head;

        for (int j = 1; j < i; j ++) {
            previous = previous -> next;
        }
    }

    CNode<T>* newNode = new CNode<T>{value, previous -> next};
    previous -> next = newNode;

    if (previous == tail) {
        tail = newNode;
    }

    size ++;
    return true;
}

// 删除第 i 个元素 / Delete element at position i. Time: O(n).
template <typename T>
bool CircularLinkedList<T>::ListDelete(int i, T& deletedValue) {
    if (i < 1 || i > size) {
        return false;
    }

    CNode<T>* previous = head;

    for (int j = 1; j < i; j ++) {
        previous = previous -> next;
    }

    CNode<T>* target = previous -> next;
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

#endif  // DSCPP_CIRCULAR_LINKED_LIST_TEMPLATE_IMPL
