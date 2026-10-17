# Data-Structures-CPP

A beginner-friendly collection of data structures implemented from scratch in C++17, without relying on STL containers.

一个面向数据结构初学者的 C++17 开源代码库：从底层实现常见数据结构，注重**原理清晰、代码易读、接口可复用**。

## 项目目标 / Goals

- **从零实现**：使用动态数组、指针等基础语言特性自行实现数据结构，不使用 `std::vector`、`std::list` 等容器替代核心实现。
- **教材为主**：以严蔚敏、吴伟民《数据结构（C语言版）》的抽象数据类型与算法思想为主要依据，用 C++17 重新实现。
- **便于学习**：保留容易理解的操作过程；函数附有简短的中英双语说明与时间复杂度。
- **方便复用**：优先使用 `template <typename T>` 编写通用数据结构，避免与具体业务类型耦合。
- **保持精简**：主要维护 `include/` 与 `src/`，在本地编译、验证后提交稳定代码。

> **说明 / Note:** 不依赖 STL **容器**不等于完全禁用 C++ 标准库；必要的标准语言设施和基础库功能可以使用。

## 项目结构 / Structure

```text
Data-Structures-CPP/
├── include/
│   └── sequential_list.h       # Public interface / 对外接口
├── src/
│   └── sequential_list.cpp     # Template implementation / 模板实现
├── .gitignore
├── LICENSE
└── README.md
```

## 实现进度 / Implementations

| 数据结构 / Data structure | 文件 / Files | 状态 / Status |
| --- | --- | --- |
| 顺序表 / Sequential List | `sequential_list.h` · `sequential_list.cpp` | 已实现 / Implemented |

其他数据结构将随学习进度逐步加入。 / More data structures will be added progressively.

### 顺序表 / Sequential List

- 使用动态数组存储元素，支持 `int`、`double`、`std::string` 等满足类型要求的数据类型。
- **逻辑位序从 1 开始**，与教材的线性表操作习惯一致。
- 初始容量为 `4`，空间不足时每次增加 `4` 个元素。
- 暂不支持复制或移动顺序表对象。

| 接口 / API | 功能 / Purpose | 时间复杂度 / Time |
| --- | --- | --- |
| `SequentialList()` | 创建空表 / Create an empty list | O(1) |
| `ClearList()` | 逻辑清空 / Logically clear the list | O(1) |
| `ListEmpty()` | 判断是否为空 / Check whether empty | O(1) |
| `ListLength()` | 获取长度 / Get the length | O(1) |
| `Capacity()` | 获取容量 / Get the capacity | O(1) |
| `GetElem(i, value)` | 读取第 `i` 个元素 / Read an element | O(1) |
| `PutElem(i, value)` | 修改第 `i` 个元素 / Replace an element | O(1) |
| `ListInsert(i, value)` | 在第 `i` 个位置插入 / Insert an element | O(n) |
| `ListDelete(i, value)` | 删除第 `i` 个元素并返回其值 / Delete an element | O(n) |

上述复杂度按元素复制与赋值为常数时间计算；扩容时需要 O(n) 次元素复制。`ClearList()` 仅将逻辑长度置零，保留底层容量与已分配的元素对象。

`GetElem`、`PutElem`、`ListInsert` 和 `ListDelete` 在位序无效时返回 `false`；在合法位序下，元素操作或内存分配仍可能抛出异常。当前实现要求 `T` 可默认构造、复制构造并复制赋值。

## 快速开始 / Quick Start

无需额外构建系统，只需支持 C++17 的编译器。 / Only a C++17-compatible compiler is required.

在仓库根目录新建临时文件 `demo.cpp`：

```cpp
#include "sequential_list.h"

#include <iostream>

int main() {
    dscpp::SequentialList<int> numbers;

    numbers.ListInsert(1, 10);
    numbers.ListInsert(2, 20);
    numbers.ListInsert(2, 15);

    int value = 0;
    if (numbers.GetElem(2, value)) {
        std::cout << value << '\n';  // 15
    }

    int deletedValue = 0;
    numbers.ListDelete(2, deletedValue);

    std::cout << numbers.ListLength() << '\n';  // 2
    return 0;
}
```

使用 GCC / MinGW-w64 编译并运行：

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude demo.cpp -o demo.exe
```

在 Windows CMD 中运行 `demo.exe`；在 PowerShell 中运行 `./demo.exe`。

> **模板实现说明 / Template note:** `sequential_list.h` 已引入相应的 `src/sequential_list.cpp` 模板定义。使用者只需包含头文件，**不要将模板 `.cpp` 再单独作为普通源文件编译**。复用时请保留 `include/` 与 `src/` 的相对目录关系。

## 参考资料 / References

1. 严蔚敏、吴伟民：《数据结构（C语言版）》——主要依据 / Primary textbook.
2. 程杰：《大话数据结构》——概念辅助 / Supplementary explanations.
3. Robert Sedgewick、Kevin Wayne：《算法（第4版）》——算法分析参考 / Algorithm analysis reference.

本仓库代码独立编写，不收录教材扫描件或未经授权的第三方代码。

## 许可证 / License

本项目采用 **GNU Affero General Public License v3.0 only（AGPL-3.0-only）** 开源。详见 [LICENSE](LICENSE)。

This project is licensed under **AGPL-3.0-only**. See [LICENSE](LICENSE) for details.
