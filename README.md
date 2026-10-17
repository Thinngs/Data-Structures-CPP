# Data-Structures-CPP

A beginner-friendly C++ data structures library built from scratch without STL containers, featuring reusable implementations and clear documentation.

> **Project status:** early development. The build/test infrastructure is ready; data structures are not implemented yet.

## Project goals / 项目目标

本项目以学习数据结构底层原理为核心，用 **C++17** 从零实现可复用的数据结构，并提供易于阅读、测试和扩展的接口。

- 不使用 `std::vector`、`std::list`、`std::stack`、`std::queue`、`std::map` 等现成 STL 容器替代数据结构实现。
- 不用 `std::sort` 等现成算法代替课程中需要亲自实现的算法。
- 允许使用编译、输入输出、异常、基础类型等必要的 C++ 标准语言及库设施。
- 优先遵循教材的数据结构定义与算法语义，以自然、可运行的 C++ 代码实现。
- 提供清晰的接口、复杂度分析、边界条件测试及使用示例。

## References / 参考教材

1. 严蔚敏、吴伟民：《数据结构（C语言版）》——主要教学依据。
2. 程杰：《大话数据结构》——辅助理解。
3. Robert Sedgewick、Kevin Wayne：《算法（第4版）》——算法设计与分析参考。

本项目自行编写代码，不包含教材全文、扫描件或未经授权的第三方实现。

## Repository layout / 目录结构

```text
.
├── include/       # Public .h interfaces / 公开接口
├── src/           # .cpp implementations / 实现
├── tests/         # Tests / 测试
├── examples/      # Usage examples / 使用示例
├── .github/       # Contribution templates
└── CMakeLists.txt # CMake project
```

对于含有模板的类，定义可能需要放在头文件或 `.tpp` 中，以保证实例化时定义可见。我们不会为了强行分离 `.h`/`.cpp` 而牺牲正确性。

## Build and test / 构建与测试

Requires a C++17 compiler and CMake 3.16 or newer.

```bash
cmake -S . -B build -DDSCPP_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

如使用 Visual Studio 等多配置生成器，可在构建和测试命令中添加 `--config Debug`、`-C Debug`。

目前的 CTest 项目仅检查 C++17 编译配置和测试接线。正式的数据结构测试将随模块逐步添加。

## Contributing / 参与贡献

请先阅读 [CONTRIBUTING.md](CONTRIBUTING.md) 和 [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)。
维护者在本地开发、编译和测试，确认改动后再提交 GitHub。外部贡献建议通过 Pull Request 提交，并附带必要的测试与复杂度说明。

## License / 许可证

Licensed under the **GNU Affero General Public License v3.0 only** (`AGPL-3.0-only`).
See [LICENSE](LICENSE) for the complete license text.
