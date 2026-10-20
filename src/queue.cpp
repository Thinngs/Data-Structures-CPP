// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_QUEUE_TEMPLATE_IMPL
#define DSCPP_QUEUE_TEMPLATE_IMPL

#include "../include/queue.h"

#include <limits>
#include <stdexcept>

namespace dscpp {

// 创建空队列 / Create an empty queue. Time: O(capacity).
template <typename T>
Queue<T>::Queue(int initialCapacity) {
    queue.capacity = initialCapacity > 0 ? initialCapacity : kInitialCapacity;
    queue.data = new T[queue.capacity];
}

// 释放存储空间 / Release storage. Time: O(capacity).
template <typename T>
Queue<T>::~Queue() {
    delete[] queue.data;
}

// 判断队列是否已满 / Check whether the queue is full. Time: O(1).
template <typename T>
bool Queue<T>::QueueFull() const noexcept {
    return queue.size == queue.capacity;
}

// 扩容为原来的两倍 / Double the capacity. Time: O(n).
template <typename T>
void Queue<T>::Expand() {
    if (queue.capacity > std::numeric_limits<int>::max() / 2) {
        throw std::length_error("Queue capacity overflow");
    }

    const int newCapacity = queue.capacity * 2;
    T* newData = new T[newCapacity];

    try {
        int index = queue.front;

        for (int i = 0; i < queue.size; i ++) {
            newData[i] = queue.data[index];
            index ++;

            if (index == queue.capacity) {
                index = 0;
            }
        }
    } catch (...) {
        delete[] newData;
        throw;
    }

    delete[] queue.data;
    queue.data = newData;
    queue.capacity = newCapacity;
    queue.front = 0;
    queue.rear = queue.size;
}

// 逻辑清空队列（保留容量）/ Clear logically (retain capacity). Time: O(1).
template <typename T>
void Queue<T>::ClearQueue() noexcept {
    queue.front = 0;
    queue.rear = 0;
    queue.size = 0;
}

// 判断队列是否为空 / Check whether the queue is empty. Time: O(1).
template <typename T>
bool Queue<T>::QueueEmpty() const noexcept {
    return queue.size == 0;
}

// 获取队列长度 / Get the queue length. Time: O(1).
template <typename T>
int Queue<T>::QueueLength() const noexcept {
    return queue.size;
}

// 获取当前容量 / Get the current capacity. Time: O(1).
template <typename T>
int Queue<T>::Capacity() const noexcept {
    return queue.capacity;
}

// 读取队头元素 / Read the front element. Time: O(1).
template <typename T>
bool Queue<T>::GetFront(T& value) const {
    if (QueueEmpty()) {
        return false;
    }

    value = queue.data[queue.front];
    return true;
}

// 入队（均摊常数时间）/ Enqueue an element. Time: O(1) amortized, O(n) on expansion.
template <typename T>
bool Queue<T>::Enqueue(const T& value) {
    // 提前复制，防止扩容时 value 引用旧数组元素 / Copy before possible reallocation.
    T insertedValue = value;

    if (QueueFull()) {
        Expand();
    }

    queue.data[queue.rear] = insertedValue;
    queue.rear ++;

    if (queue.rear == queue.capacity) {
        queue.rear = 0;
    }

    queue.size ++;
    return true;
}

// 出队 / Dequeue the front element. Time: O(1).
template <typename T>
bool Queue<T>::Dequeue(T& value) {
    if (QueueEmpty()) {
        return false;
    }

    value = queue.data[queue.front];
    queue.front ++;

    if (queue.front == queue.capacity) {
        queue.front = 0;
    }

    queue.size --;
    return true;
}

}  // namespace dscpp

#endif  // DSCPP_QUEUE_TEMPLATE_IMPL
