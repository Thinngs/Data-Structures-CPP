// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_QUEUE_H
#define DSCPP_QUEUE_H

namespace dscpp {

// 循环队列存储结构 / Circular queue storage structure.
template <typename T>
struct QueueData {
    T* data = nullptr;
    int front = 0;
    int rear = 0;
    int size = 0;
    int capacity = 0;
};

// 可扩容的通用循环队列（先进先出）/ Generic resizable circular queue (FIFO).
// T 需支持默认构造、复制构造和复制赋值。
// T must support default construction, copy construction, and copy assignment.
template <typename T>
class Queue {
private:
    static constexpr int kInitialCapacity = 8;

    QueueData<T> queue;

    // 判断队列是否已满 / Check whether the queue is full. Time: O(1).
    bool QueueFull() const noexcept;

    // 扩容为原来的两倍 / Double the capacity. Time: O(n).
    void Expand();

public:
    // 创建空队列 / Create an empty queue. Time: O(capacity).
    explicit Queue(int initialCapacity = kInitialCapacity);

    // 释放存储空间 / Release storage. Time: O(capacity).
    ~Queue();

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    // 逻辑清空队列（保留容量）/ Clear logically (retain capacity). Time: O(1).
    void ClearQueue() noexcept;

    // 判断队列是否为空 / Check whether the queue is empty. Time: O(1).
    bool QueueEmpty() const noexcept;

    // 获取队列长度 / Get the queue length. Time: O(1).
    int QueueLength() const noexcept;

    // 获取当前容量 / Get the current capacity. Time: O(1).
    int Capacity() const noexcept;

    // 读取队头元素 / Read the front element. Time: O(1).
    bool GetFront(T& value) const;

    // 入队（均摊常数时间）/ Enqueue an element. Time: O(1) amortized, O(n) on expansion.
    bool Enqueue(const T& value);

    // 出队 / Dequeue the front element. Time: O(1).
    bool Dequeue(T& value);
};

}  // namespace dscpp

// 模板定义必须可见 / Template definitions must be visible to callers.
#include "../src/queue.cpp"

#endif  // DSCPP_QUEUE_H
