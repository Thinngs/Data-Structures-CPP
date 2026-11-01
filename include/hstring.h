// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_HSTRING_H
#define DSCPP_HSTRING_H

#include <utility>

namespace dscpp {

// 堆分配顺序串的存储结构 / Storage structure of a heap-allocated string.
struct HStringData {
    char* ch = nullptr;
    int length = 0;
};

// 堆分配顺序串 / Heap-allocated sequential string.
class HString {
private:
    HStringData data;

    // 释放内部存储空间 / Release internal storage. Time: O(1).
    void Release() noexcept;

    // 检查位序是否合法 / Check whether a position is valid. Time: O(1).
    bool ValidPosition(int pos, bool allowEnd = false) const noexcept;

    // 构造 KMP next 数组 / Build the KMP prefix table. Time: O(m).
    static void GetNext(const HString& T, int* next);

public:
    // 创建空串 / Create an empty string. Time: O(1).
    HString() = default;

    // 深拷贝构造 / Deep-copy construction. Time: O(n).
    HString(const HString& other);

    // 深拷贝赋值 / Deep-copy assignment. Time: O(n).
    HString& operator=(const HString& other);

    // 移动构造 / Move construction. Time: O(1).
    HString(HString&& other) noexcept;

    // 移动赋值 / Move assignment. Time: O(1).
    HString& operator=(HString&& other) noexcept;

    // 释放动态存储空间 / Release dynamic storage. Time: O(1).
    ~HString();

    // 将 C 字符串赋给当前串 / Assign a C string. Time: O(n).
    bool StrAssign(const char* chars);

    // 将串 S 复制到当前串 / Copy string S to this string. Time: O(n).
    bool StrCopy(const HString& S);

    // 获取串长 / Get string length. Time: O(1).
    int StrLength() const noexcept;

    // 获取子串并保存到当前串 / Extract a substring into this string. Time: O(len).
    bool SubString(const HString& S, int pos, int len);

    // 按字典序比较当前串与 T / Compare this string with T lexicographically. Time: O(min(n,m)).
    int StrCompare(const HString& T) const noexcept;

    // 连接 S1 和 S2 并保存到当前串 / Concatenate S1 and S2 into this string. Time: O(n + m).
    bool Concat(const HString& S1, const HString& S2);

    // 清空当前串并释放空间 / Clear this string and release storage. Time: O(1).
    void ClearString() noexcept;

    // 查找子串 T，返回首次出现的位序 / Find the first occurrence of T. Time: O(nm).
    int Index(const HString& T, int pos = 1) const noexcept;

    // 将当前串中不重叠的 T 替换为 V / Replace non-overlapping occurrences of T with V. Time: O(n + m + k).
    bool Replace(const HString& T, const HString& V);

    // 判断当前串是否为空 / Check whether this string is empty. Time: O(1).
    bool StrEmpty() const noexcept;

    // 在第 pos 个字符之前插入 T / Insert T before position pos. Time: O(n + m).
    bool StrInsert(int pos, const HString& T);

    // 删除从第 pos 个字符开始的 len 个字符 / Delete len characters from position pos. Time: O(n).
    bool StrDelete(int pos, int len);

    // 销毁当前串的内容 / Destroy the string contents. Time: O(1).
    void DestroyString() noexcept;

    // 读取指定字符 / Read a character at position pos. Time: O(1).
    bool GetChar(int pos, char& value) const noexcept;
};

}  // namespace dscpp

#endif  // DSCPP_HSTRING_H
