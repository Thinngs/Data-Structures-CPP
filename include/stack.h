// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_STACK_H
#define DSCPP_STACK_H

namespace dscpp {

// 顺序栈存储结构 / Sequential stack storage structure.
template <typename T>
struct StackData {
    static constexpr int kCapacity = 100;

    T data[kCapacity];
    int top = -1;
};

// 固定容量通用顺序栈（后进先出）/ Generic fixed-capacity sequential stack (LIFO).
// T 需支持默认构造、复制构造和复制赋值。
// T must support default construction, copy construction, and copy assignment.
template <typename T>
class Stack {
private:
    StackData<T> stack;

    // 判断栈是否已满 / Check whether the stack is full. Time: O(1).
    bool StackFull() const noexcept;

public:
    // 创建空栈 / Create an empty stack. Time: O(capacity) for element construction.
    Stack();

    // 销毁栈 / Destroy the stack. Time: O(capacity) for element destruction.
    ~Stack() = default;

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    // 逻辑清空栈 / Clear the stack logically. Time: O(1).
    void ClearStack() noexcept;

    // 判断栈是否为空 / Check whether the stack is empty. Time: O(1).
    bool StackEmpty() const noexcept;

    // 获取栈内元素个数 / Get the number of elements. Time: O(1).
    int StackLength() const noexcept;

    // 获取固定容量 / Get the fixed capacity. Time: O(1).
    int Capacity() const noexcept;

    // 读取栈顶元素 / Read the top element. Time: O(1).
    bool GetTop(T& value) const;

    // 压入元素（栈满返回 false）/ Push an element (false if full). Time: O(1).
    bool Push(const T& value);

    // 弹出栈顶元素 / Pop the top element. Time: O(1).
    bool Pop(T& value);
};

}  // namespace dscpp

// 模板定义必须可见 / Template definitions must be visible to callers.
#include "../src/stack.cpp"

#endif  // DSCPP_STACK_H
