# Data Structures CPP

> Data structure implementations written in C++17.

本项目用于记录数据结构课程的学习过程，并将各类数据结构整理为可复用的 C++ 实现。项目采用头文件与源文件分离的组织方式，并使用 CMake 管理构建。

## Implementations

当前项目包含以下模块：

| Category | Module |
|---|---|
| Linear List | Sequential List |
| Linked List | Singly Linked List |
| Linked List | Doubly Linked List |
| Linked List | Circular Linked List |
| Linked List | Doubly Circular Linked List |
| Stack | Stack |
| Queue | Queue |
| String | SString |
| String | HString |
| String | IString |

模块的具体接口、参数约定和操作说明以对应头文件中的声明及注释为准。

## Project Structure

```text
Data-Structures-CPP/
│
├── build/                              # Generated build files
│
├── include/                            # Header files
│   ├── circular_linked_list.h
│   ├── doubly_circular_linked_list.h
│   ├── doubly_linked_list.h
│   ├── hstring.h
│   ├── istring.h
│   ├── queue.h
│   ├── sequential_list.h
│   ├── singly_linked_list.h
│   ├── sstring.h
│   └── stack.h
│
├── src/                                 # Source files
│   ├── circular_linked_list.cpp
│   ├── doubly_circular_linked_list.cpp
│   ├── doubly_linked_list.cpp
│   ├── hstring.cpp
│   ├── istring.cpp
│   ├── queue.cpp
│   ├── sequential_list.cpp
│   ├── singly_linked_list.cpp
│   ├── sstring.cpp
│   └── stack.cpp
│
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

`build/` contains generated build files and compiled outputs. It is not a source directory.

## Requirements

- C++17-compatible compiler
- CMake 3.16 or later

Supported toolchains include GCC, Clang, and MSVC.

## Build

Run these commands from the project root:

```bash
cmake -S . -B build
cmake --build build --config Release
```

The project builds a static library named `dscpp`:

- Windows: `dscpp.lib`
- Linux: `libdscpp.a`
- macOS: `libdscpp.a`

This repository currently builds a library, not a standalone executable. There is no project-level `main.cpp`.

## Use in Another CMake Project

The repository can be added as a subdirectory:

```cmake
add_subdirectory(path/to/Data-Structures-CPP)

add_executable(example main.cpp)
target_link_libraries(example PRIVATE dscpp::dscpp)
```

The library exports the `include/` directory, so headers can be included by name:

```cpp
#include "sstring.h"
#include "hstring.h"
#include "istring.h"
```

## Implementation Notes

- The project uses C++17.
- Public declarations are organized in `include/`; non-template implementations are organized in `src/`.
- `sequential_list.h` includes `sequential_list.cpp` because the latter contains template definitions. Therefore, `sequential_list.cpp` is not added as an independent source in `CMakeLists.txt`.
- Template types implemented in `.cpp` files must have the required explicit instantiations in those implementation files.

## License

This project is licensed under the **GNU Affero General Public License v3.0 only**.

SPDX-License-Identifier:

```text
AGPL-3.0-only
```

See [LICENSE](LICENSE) for the full license text.
