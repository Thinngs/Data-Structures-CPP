# Contributing to Data-Structures-CPP

Thank you for helping improve this beginner-oriented data structures project.

## Before contributing

- Please open an issue for substantial design changes before implementing them.
- Keep the primary textbook's abstract data type semantics recognizable, while writing idiomatic C++17.
- Implement the core storage structure and algorithm manually. Do not substitute STL containers or standard library algorithms for the data structure/algorithm being taught.
- Do not copy code, textbook pages, figures, or explanations without compatible permission and attribution.

## Code conventions

- Public headers go under `include/`; non-template implementations go under `src/`.
- Put tests under `tests/` and beginner-facing demos under `examples/`.
- Use 4 spaces, UTF-8, LF line endings, and the repository's `.clang-format` file.
- Prefer `UpperCamelCase` for class names, `lowerCamelCase` for methods and variables, and `snake_case` for file names.
- Prefer `struct` for simple nodes and `class` to encapsulate the data structure, where appropriate.
- Document index conventions, invalid-input behavior, time/space complexity, and memory ownership.
- For types owning dynamic memory, implement or explicitly disable copy and move operations as appropriate.
- Original C++ files must begin with the SPDX license identifier `AGPL-3.0-only` and a correct copyright-holder line; use only attribution you are entitled to make.
- Do not commit build outputs, binaries, temporary files, or copies of source textbooks.

## Build and test

```bash
cmake -S . -B build -DDSCPP_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

For multi-configuration generators, use `cmake --build build --config Debug` and `ctest --test-dir build -C Debug --output-on-failure`.

## Pull requests

1. Create a focused branch; avoid unrelated changes.
2. Include tests for normal, empty, boundary, and failure cases where relevant.
3. Describe the algorithm, complexity, ownership rules, and any deviations from the textbook.
4. Run the tests and formatting checks.
5. For external contributions, open a Pull Request for review. The maintainer verifies changes locally before merging. The maintainer may push tested updates directly.

By contributing, you agree that your submitted contribution is licensed under the repository's `AGPL-3.0-only` license unless an explicit compatible arrangement is agreed.
