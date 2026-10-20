# Data-Structures-CPP

A beginner-friendly collection of data structures implemented from scratch in C++17, without relying on STL containers for the underlying storage.

面向初学者的 C++17 数据结构开源代码库。遵循教材的抽象数据类型（ADT）与基本算法思想，注重**实现原理清晰、接口统一、代码易读、方便复用**。

## 项目目标 / Goals

- **从零实现 / From scratch**：使用动态数组和指针实现基本存储结构，不使用 `std::vector`、`std::list`、`std::stack`、`std::queue` 等现成容器代替核心实现。
- **通用模板 / Generic templates**：使用 `template <typename T>`，避免绑定习题中的特定数据类型。
- **教材导向 / Textbook-oriented**：优先参考严蔚敏、吴伟民《数据结构（C语言版）》的概念、术语和基本操作。
- **易于学习 / Readability**：统一命名、1-based 线性表位序，并为函数提供简短的中英双语说明与时间复杂度。

> 不使用 STL 容器不等于禁用所有 C++ 标准库功能。/ Avoiding STL containers does not mean avoiding the entire C++ standard library.

## 项目结构 / Structure

```text
Data-Structures-CPP/
├── include/
│   ├── sequential_list.h
│   ├── singly_linked_list.h
│   ├── circular_linked_list.h
│   ├── doubly_linked_list.h
│   ├── doubly_circular_linked_list.h
│   ├── stack.h
│   └── queue.h
├── src/
│   ├── sequential_list.cpp
│   ├── singly_linked_list.cpp
│   ├── circular_linked_list.cpp
│   ├── doubly_linked_list.cpp
│   ├── doubly_circular_linked_list.cpp
│   ├── stack.cpp
│   └── queue.cpp
├── CMakeLists.txt
├── .gitignore
├── LICENSE
└── README.md
```

`include/` 提供公开接口，`src/` 提供模板实现。/ Public declarations live in `include/`; template implementations live in `src/`.

## 已实现的数据结构 / Implementations

| 数据结构 / Data structure | 类模板 / Class template | 底层设计 / Design |
| --- | --- | --- |
| 顺序表 / Sequential List | `SequentialList<T>` | 动态数组；初始容量 4，按 4 递增 |
| 单链表 / Singly Linked List | `SinglyLinkedList<T>` | 带头结点、尾指针；非循环 |
| 循环单链表 / Circular Linked List | `CircularLinkedList<T>` | 带头结点、尾指针；尾结点指回头结点 |
| 双链表 / Doubly Linked List | `DoublyLinkedList<T>` | 带头结点、尾指针；非循环、双向就近查找 |
| 双向循环链表 / Doubly Circular Linked List | `DoublyCircularLinkedList<T>` | 带头结点；头尾双向成环、双向就近查找 |
| 顺序栈 / Stack | `Stack<T>` | 固定容量 100，后进先出（LIFO） |
| 循环队列 / Queue | `Queue<T>` | 默认容量 8，容量不足时翻倍，先进先出（FIFO） |

### 基本接口 / Core APIs

**线性表 / Linear lists**：五种线性表都支持 `ClearList()`、`ListEmpty()`、`ListLength()`、`GetElem(i, value)`、`ListInsert(i, value)`、`ListDelete(i, value)`。

- `SequentialList<T>` 还提供 `Capacity()`、`PutElem(i, value)`。
- `CircularLinkedList<T>`、`DoublyLinkedList<T>`、`DoublyCircularLinkedList<T>` 还提供 `PutElem(i, value)`、`LocateElem(value)`、`PrevElem(value, result)`、`NextElem(value, result)`。
- `SinglyLinkedList<T>` 当前只提供上述公共基础操作。

所有线性表的有效元素位序从 **1** 开始；插入位置为 `1` 至 `length + 1`，查询和删除位置为 `1` 至 `length`。按值查找返回首次匹配的位序，未找到返回 `0`；前驱和后继查询在表头、表尾处不跨越边界，即使底层是循环链表也一样。

**栈 / Stack**：`ClearStack()`、`StackEmpty()`、`StackLength()`、`Capacity()`、`GetTop(value)`、`Push(value)`、`Pop(value)`。固定容量满时，`Push` 返回 `false`。

**队列 / Queue**：`ClearQueue()`、`QueueEmpty()`、`QueueLength()`、`Capacity()`、`GetFront(value)`、`Enqueue(value)`、`Dequeue(value)`。`Queue<T>` 可通过构造函数参数自定义初始容量，默认值为 `8`。

### 时间复杂度 / Time complexity

| 数据结构 / Structure | 查询 / Read | 插入 / Insert | 删除 / Delete |
| --- | --- | --- | --- |
| 顺序表 | O(1) | O(n) | O(n) |
| 单链表 | O(n) | O(n)，尾插 O(1) | O(n) |
| 循环单链表 | O(n) | O(n)，尾插 O(1) | O(n) |
| 双链表 | O(n) | O(n)，首尾插入 O(1) | O(n)，首尾删除 O(1) |
| 双向循环链表 | O(n) | O(n)，首尾插入 O(1) | O(n)，首尾删除 O(1) |
| 顺序栈 | 栈顶 O(1) | 入栈 O(1) | 出栈 O(1) |
| 循环队列 | 队头 O(1) | 入队均摊 O(1) | 出队 O(1) |

以上按单次元素复制、比较和赋值为常数时间估算。顺序表和循环队列扩容时需要 O(n) 时间；队列的均摊复杂度基于容量翻倍策略。链表清空为 O(n)，数组式顺序表、栈与队列的逻辑清空为 O(1)。

**类型与异常 / Type and exception notes**：当前模板实现要求 `T` 支持默认构造、复制构造和复制赋值；按值查找要求 `operator==`。对象暂不支持复制或移动。非法位序、空栈或空队列等情况由对应的 `bool` 操作返回 `false`；有效操作仍可能因内存分配或元素复制、赋值而抛出异常。

## 快速开始 / Quick Start

### 直接使用 G++ / Direct compilation

在仓库根目录创建临时的 `demo.cpp`：

```cpp
#include "sequential_list.h"
#include "doubly_linked_list.h"
#include "stack.h"
#include "queue.h"

#include <iostream>

int main() {
    dscpp::SequentialList<int> numbers;
    numbers.ListInsert(1, 10);
    numbers.ListInsert(2, 20);

    dscpp::DoublyLinkedList<int> linked;
    linked.ListInsert(1, 30);

    dscpp::Stack<int> stack;
    stack.Push(40);

    dscpp::Queue<int> queue;
    queue.Enqueue(50);

    int value = 0;
    numbers.GetElem(2, value);
    std::cout << value << '\n';  // 20
    linked.GetElem(1, value);
    std::cout << value << '\n';  // 30
    stack.Pop(value);
    std::cout << value << '\n';  // 40
    queue.Dequeue(value);
    std::cout << value << '\n';  // 50

    return 0;
}
```

在仓库根目录编译：

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude demo.cpp -o demo.exe
```

Windows CMD 运行 `demo.exe`；PowerShell 运行 `./demo.exe`。

### CMake 本地构建检查 / Local CMake check

要求 CMake 3.16+ 及 C++17 编译器。使用 MinGW-w64 的示例：

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
ctest --test-dir build --output-on-failure
```

配置时默认启用 `DSCPP_BUILD_CHECK`（仅在独立构建本仓库时），在 `build/` 内生成一个用于检查全部七种数据结构的临时可执行程序；CTest 运行基础功能检查。该检查**不是完整的单元测试套件**，不会创建或要求提交 `tests/` 目录。

如只需在其他 CMake 工程中引用此模板库：

```cmake
add_subdirectory(path/to/Data-Structures-CPP)
target_link_libraries(your_target PRIVATE data_structures)
```

**模板实现说明 / Template implementation:** 每个 `.h` 都包含其对应的 `src/*.cpp` 模板定义。因此使用者只需 `#include` 相关头文件，**不要将这些模板 `.cpp` 文件再单独加入编译源文件列表**；复制或引用时须保持 `include/` 和 `src/` 的相对目录结构。

## 参考资料 / References

1. 严蔚敏、吴伟民：《数据结构（C语言版）》——主要依据 / Primary textbook.
2. 程杰：《大话数据结构》——概念辅助 / Supplementary reading.
3. Robert Sedgewick、Kevin Wayne：《算法（第4版）》——算法与复杂度参考 / Algorithm reference.

代码独立编写；本仓库不收录教材扫描件或未经授权的第三方代码。

## 许可证 / License

本项目采用 **GNU Affero General Public License v3.0 only（AGPL-3.0-only）** 开源。详见 [LICENSE](LICENSE)。

This project is licensed under **AGPL-3.0-only**. See [LICENSE](LICENSE) for details.
