// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_DOUBLY_CIRCULAR_LINKED_LIST_TEMPLATE_IMPL
#define DSCPP_DOUBLY_CIRCULAR_LINKED_LIST_TEMPLATE_IMPL

#include "../include/doubly_circular_linked_list.h"

namespace dscpp {

// 创建空双向循环链表 / Create an empty doubly circular list. Time: O(1).
template <typename T>
DoublyCircularLinkedList<T>::DoublyCircularLinkedList() {
    head = new DCNode<T>;
    head -> prior = head;
    head -> next = head;
    size = 0;
}

// 释放全部结点 / Release all nodes. Time: O(n).
template <typename T>
DoublyCircularLinkedList<T>::~DoublyCircularLinkedList() {
    ClearList();
    delete head;
}

// 从较近的一端查找第 i 个结点 / Find node i from the nearer end. Time: O(n).
template <typename T>
DCNode<T>* DoublyCircularLinkedList<T>::GetNode(int i) const noexcept {
    if (i < 1 || i > size) {
        return nullptr;
    }

    DCNode<T>* current;

    if (i <= size / 2) {
        current = head -> next;

        for (int j = 1; j < i; j ++) {
            current = current -> next;
        }
    } else {
        current = head -> prior;

        for (int j = size; j > i; j --) {
            current = current -> prior;
        }
    }

    return current;
}

// 清空链表 / Clear the list. Time: O(n).
template <typename T>
void DoublyCircularLinkedList<T>::ClearList() noexcept {
    DCNode<T>* current = head -> next;

    while (current != head) {
        DCNode<T>* tmp = current;
        current = current -> next;
        delete tmp;
    }

    head -> next = head;
    head -> prior = head;
    size = 0;
}

// 判断是否为空 / Check whether empty. Time: O(1).
template <typename T>
bool DoublyCircularLinkedList<T>::ListEmpty() const noexcept {
    return size == 0;
}

// 获取链表长度 / Get the list length. Time: O(1).
template <typename T>
int DoublyCircularLinkedList<T>::ListLength() const noexcept {
    return size;
}

// 读取第 i 个元素 / Read element at position i. Time: O(n).
template <typename T>
bool DoublyCircularLinkedList<T>::GetElem(int i, T& value) const {
    DCNode<T>* current = GetNode(i);

    if (current == nullptr) {
        return false;
    }

    value = current -> data;
    return true;
}

// 修改第 i 个元素 / Replace element at position i. Time: O(n).
template <typename T>
bool DoublyCircularLinkedList<T>::PutElem(int i, const T& value) {
    DCNode<T>* current = GetNode(i);

    if (current == nullptr) {
        return false;
    }

    current -> data = value;
    return true;
}

// 查找元素首次出现的位序（未找到返回 0）/ Find the first position of a value (0 if absent). Time: O(n).
template <typename T>
int DoublyCircularLinkedList<T>::LocateElem(const T& value) const {
    DCNode<T>* current = head -> next;

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
bool DoublyCircularLinkedList<T>::PrevElem(const T& value, T& previousValue) const {
    DCNode<T>* current = head -> next;

    while (current != head) {
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
bool DoublyCircularLinkedList<T>::NextElem(const T& value, T& nextValue) const {
    DCNode<T>* current = head -> next;

    while (current != head) {
        if (current -> data == value) {
            if (current -> next == head) {
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
bool DoublyCircularLinkedList<T>::ListInsert(int i, const T& value) {
    if (i < 1 || i - 1 > size) {
        return false;
    }

    // 尾插直接使用头结点 / Append directly before the dummy head.
    DCNode<T>* nextNode = (i - 1 == size) ? head : GetNode(i);
    DCNode<T>* previousNode = nextNode -> prior;
    DCNode<T>* newNode = new DCNode<T>{value, previousNode, nextNode};

    previousNode -> next = newNode;
    nextNode -> prior = newNode;
    size ++;
    return true;
}

// 删除第 i 个元素 / Delete element at position i. Time: O(n), O(1) at either end.
template <typename T>
bool DoublyCircularLinkedList<T>::ListDelete(int i, T& deletedValue) {
    DCNode<T>* target = GetNode(i);

    if (target == nullptr) {
        return false;
    }

    deletedValue = target -> data;

    target -> prior -> next = target -> next;
    target -> next -> prior = target -> prior;
    delete target;
    size --;
    return true;
}

}  // namespace dscpp

#endif  // DSCPP_DOUBLY_CIRCULAR_LINKED_LIST_TEMPLATE_IMPL
