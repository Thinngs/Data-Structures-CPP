// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_DOUBLY_LINKED_LIST_TEMPLATE_IMPL
#define DSCPP_DOUBLY_LINKED_LIST_TEMPLATE_IMPL

#include "../include/doubly_linked_list.h"

namespace dscpp {

// 创建空双链表 / Create an empty doubly linked list. Time: O(1).
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = new DLNode<T>;
    head -> prior = nullptr;
    head -> next = nullptr;
    tail = head;
    size = 0;
}

// 释放全部结点 / Release all nodes. Time: O(n).
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    ClearList();
    delete head;
}

// 从较近的一端查找第 i 个结点 / Find node i from the nearer end. Time: O(n).
template <typename T>
DLNode<T>* DoublyLinkedList<T>::GetNode(int i) const noexcept {
    if (i < 1 || i > size) {
        return nullptr;
    }

    DLNode<T>* current;

    if (i <= size / 2) {
        current = head -> next;

        for (int j = 1; j < i; j ++) {
            current = current -> next;
        }
    } else {
        current = tail;

        for (int j = size; j > i; j --) {
            current = current -> prior;
        }
    }

    return current;
}

// 清空链表 / Clear the list. Time: O(n).
template <typename T>
void DoublyLinkedList<T>::ClearList() noexcept {
    DLNode<T>* current = head -> next;

    while (current != nullptr) {
        DLNode<T>* tmp = current;
        current = current -> next;
        delete tmp;
    }

    head -> next = nullptr;
    tail = head;
    size = 0;
}

// 判断是否为空 / Check whether empty. Time: O(1).
template <typename T>
bool DoublyLinkedList<T>::ListEmpty() const noexcept {
    return size == 0;
}

// 获取链表长度 / Get the list length. Time: O(1).
template <typename T>
int DoublyLinkedList<T>::ListLength() const noexcept {
    return size;
}

// 读取第 i 个元素 / Read element at position i. Time: O(n).
template <typename T>
bool DoublyLinkedList<T>::GetElem(int i, T& value) const {
    DLNode<T>* current = GetNode(i);

    if (current == nullptr) {
        return false;
    }

    value = current -> data;
    return true;
}

// 修改第 i 个元素 / Replace element at position i. Time: O(n).
template <typename T>
bool DoublyLinkedList<T>::PutElem(int i, const T& value) {
    DLNode<T>* current = GetNode(i);

    if (current == nullptr) {
        return false;
    }

    current -> data = value;
    return true;
}

// 查找元素首次出现的位序（未找到返回 0）/ Find the first position of a value (0 if absent). Time: O(n).
template <typename T>
int DoublyLinkedList<T>::LocateElem(const T& value) const {
    DLNode<T>* current = head -> next;

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
bool DoublyLinkedList<T>::PrevElem(const T& value, T& previousValue) const {
    DLNode<T>* current = head -> next;

    while (current != nullptr) {
        if (current -> data == value) {
            if (current -> prior == head) {
                return false;
            }

            previousValue = current -> prior -> data;
            return true;
        }

        current = current -> next;
    }

    return false;
}

// 获取首次匹配元素的后继 / Get the successor of the first matching element. Time: O(n).
template <typename T>
bool DoublyLinkedList<T>::NextElem(const T& value, T& nextValue) const {
    DLNode<T>* current = head -> next;

    while (current != nullptr) {
        if (current -> data == value) {
            if (current -> next == nullptr) {
                return false;
            }

            nextValue = current -> next -> data;
            return true;
        }

        current = current -> next;
    }

    return false;
}

// 在第 i 个位置插入 / Insert at position i. Time: O(n), O(1) at either end.
template <typename T>
bool DoublyLinkedList<T>::ListInsert(int i, const T& value) {
    if (i < 1 || i - 1 > size) {
        return false;
    }

    // 尾插直接使用尾指针 / Use the tail pointer for appending.
    DLNode<T>* nextNode = (i - 1 == size) ? nullptr : GetNode(i);
    DLNode<T>* previousNode = (nextNode == nullptr) ? tail : nextNode -> prior;
    DLNode<T>* newNode = new DLNode<T>{value, previousNode, nextNode};

    previousNode -> next = newNode;

    if (nextNode != nullptr) {
        nextNode -> prior = newNode;
    } else {
        tail = newNode;
    }

    size ++;
    return true;
}

// 删除第 i 个元素 / Delete element at position i. Time: O(n), O(1) at either end.
template <typename T>
bool DoublyLinkedList<T>::ListDelete(int i, T& deletedValue) {
    DLNode<T>* target = GetNode(i);

    if (target == nullptr) {
        return false;
    }

    deletedValue = target -> data;

    DLNode<T>* previousNode = target -> prior;
    DLNode<T>* nextNode = target -> next;
    previousNode -> next = nextNode;

    if (nextNode != nullptr) {
        nextNode -> prior = previousNode;
    } else {
        tail = previousNode;
    }

    delete target;
    size --;
    return true;
}

}  // namespace dscpp

#endif  // DSCPP_DOUBLY_LINKED_LIST_TEMPLATE_IMPL
