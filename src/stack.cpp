// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_STACK_TEMPLATE_IMPL
#define DSCPP_STACK_TEMPLATE_IMPL

#include "../include/stack.h"

namespace dscpp {

// 创建空栈 / Create an empty stack. Time: O(capacity) for element construction.
template <typename T>
Stack<T>::Stack() {
    stack.top = -1;
}

// 判断栈是否已满 / Check whether the stack is full. Time: O(1).
template <typename T>
bool Stack<T>::StackFull() const noexcept {
    return stack.top + 1 == StackData<T>::kCapacity;
}

// 逻辑清空栈 / Clear the stack logically. Time: O(1).
template <typename T>
void Stack<T>::ClearStack() noexcept {
    stack.top = -1;
}

// 判断栈是否为空 / Check whether the stack is empty. Time: O(1).
template <typename T>
bool Stack<T>::StackEmpty() const noexcept {
    return stack.top == -1;
}

// 获取栈内元素个数 / Get the number of elements. Time: O(1).
template <typename T>
int Stack<T>::StackLength() const noexcept {
    return stack.top + 1;
}

// 获取固定容量 / Get the fixed capacity. Time: O(1).
template <typename T>
int Stack<T>::Capacity() const noexcept {
    return StackData<T>::kCapacity;
}

// 读取栈顶元素 / Read the top element. Time: O(1).
template <typename T>
bool Stack<T>::GetTop(T& value) const {
    if (StackEmpty()) {
        return false;
    }

    value = stack.data[stack.top];
    return true;
}

// 压入元素（栈满返回 false）/ Push an element (false if full). Time: O(1).
template <typename T>
bool Stack<T>::Push(const T& value) {
    if (StackFull()) {
        return false;
    }

    stack.data[stack.top + 1] = value;
    stack.top ++;
    return true;
}

// 弹出栈顶元素 / Pop the top element. Time: O(1).
template <typename T>
bool Stack<T>::Pop(T& value) {
    if (StackEmpty()) {
        return false;
    }

    value = stack.data[stack.top];
    stack.top --;
    return true;
}

}  // namespace dscpp

#endif  // DSCPP_STACK_TEMPLATE_IMPL
