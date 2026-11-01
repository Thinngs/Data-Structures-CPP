// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_SSTRING_H
#define DSCPP_SSTRING_H

namespace dscpp {

constexpr int MAXSTRLEN = 255;

// 定长顺序串的存储结构 / Storage structure of a fixed-length sequential string.
struct SStringData {
    unsigned char elem[MAXSTRLEN + 1] = {};
};

// 定长顺序串（位序从 1 开始）/ Fixed-length sequential string (1-based positions).
class SString {
private:
    SStringData data;

    // 获取实际串长 / Get the current string length. Time: O(1).
    int Length() const noexcept;

    // 检查位序是否合法 / Check whether a position is valid. Time: O(1).
    bool ValidPosition(int pos, bool allowEnd = false) const noexcept;

public:
    // 创建空串 / Create an empty string. Time: O(1).
    SString() = default;

    // 将 C 字符串赋给顺序串，超长时截断 / Assign a C string, truncating if necessary. Time: O(n).
    bool StrAssign(const char* chars);

    // 将串 S 复制到当前串 / Copy string S to this string. Time: O(n).
    bool StrCopy(const SString& S);

    // 获取串长 / Get string length. Time: O(1).
    int StrLength() const noexcept;

    // 获取子串并保存到当前串 / Extract a substring into this string. Time: O(len).
    bool SubString(const SString& S, int pos, int len);

    // 按字典序比较当前串与 T / Compare this string with T lexicographically. Time: O(min(n,m)).
    int StrCompare(const SString& T) const noexcept;

    // 连接 S1 和 S2 并保存到当前串，超长时截断 / Concatenate S1 and S2, truncating if necessary. Time: O(n + m).
    bool Concat(const SString& S1, const SString& S2);

    // 清空当前串 / Clear this string. Time: O(1).
    void ClearString() noexcept;

    // 查找子串 T，返回首次出现的位序 / Find the first occurrence of T. Time: O(nm).
    int Index(const SString& T, int pos = 1) const noexcept;

    // 将当前串中不重叠的 T 替换为 V / Replace non-overlapping occurrences of T with V. Time: O(n + k*m).
    bool Replace(const SString& T, const SString& V);

    // 判断当前串是否为空 / Check whether this string is empty. Time: O(1).
    bool StrEmpty() const noexcept;

    // 在第 pos 个字符之前插入 T / Insert T before position pos. Time: O(n + m).
    bool StrInsert(int pos, const SString& T);

    // 删除从第 pos 个字符开始的 len 个字符 / Delete len characters from position pos. Time: O(n).
    bool StrDelete(int pos, int len);

    // 销毁当前串的内容 / Destroy the string contents. Time: O(1).
    void DestroyString() noexcept;

    // 读取指定字符 / Read a character at position pos. Time: O(1).
    bool GetChar(int pos, char& value) const noexcept;
};

}  // namespace dscpp

#endif  // DSCPP_SSTRING_H
