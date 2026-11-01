// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DSCPP_LSTRING_H
#define DSCPP_LSTRING_H

namespace dscpp {

constexpr int CHUNKSIZE = 80;

// 块链串的结点结构 / Node structure of a chunked linked string.
struct Chunk {
    char ch[CHUNKSIZE] = {};
    Chunk* next = nullptr;
};

// 块链串的存储结构 / Storage structure of a chunked linked string.
struct LStringData {
    Chunk* head = nullptr;
    Chunk* tail = nullptr;
    int curlen = 0;
};

// 块链串（位序从 1 开始）/ Chunked linked string (1-based positions).
class LString {
private:
    LStringData data;

    // 释放所有结点 / Release all nodes. Time: O(n / CHUNKSIZE).
    void Release() noexcept;

    // 向当前串尾部追加一个字符 / Append one character. Amortized time: O(1).
    void AppendChar(char value);

    // 将 source 从 start 开始的 len 个字符追加到当前串 / Append a range from source. Time: O(len + n / CHUNKSIZE).
    bool AppendRange(const LString& source, int start, int len);

    // 将串内容复制到连续字符数组 / Copy string contents to a contiguous buffer. Time: O(n / CHUNKSIZE + n).
    void CopyTo(char* buffer) const noexcept;

    // 检查位序是否合法 / Check whether a position is valid. Time: O(1).
    bool ValidPosition(int pos, bool allowEnd = false) const noexcept;

    // 构造 KMP next 数组 / Build the KMP prefix table. Time: O(m).
    static void GetNext(const char* pattern, int length, int* next) noexcept;

public:
    // 创建空串 / Create an empty string. Time: O(1).
    LString() = default;

    // 深拷贝构造 / Deep-copy construction. Time: O(n).
    LString(const LString& other);

    // 深拷贝赋值 / Deep-copy assignment. Time: O(n).
    LString& operator=(const LString& other);

    // 移动构造 / Move construction. Time: O(1).
    LString(LString&& other) noexcept;

    // 移动赋值 / Move assignment. Time: O(1).
    LString& operator=(LString&& other) noexcept;

    // 释放所有结点 / Release all nodes. Time: O(n / CHUNKSIZE).
    ~LString();

    // 将 C 字符串赋给当前串 / Assign a C string. Time: O(n).
    bool StrAssign(const char* chars);

    // 将串 S 复制到当前串 / Copy string S to this string. Time: O(n).
    bool StrCopy(const LString& S);

    // 获取串长 / Get string length. Time: O(1).
    int StrLength() const noexcept;

    // 获取子串并保存到当前串 / Extract a substring into this string. Time: O(n + len).
    bool SubString(const LString& S, int pos, int len);

    // 按字典序比较当前串与 T / Compare this string with T lexicographically. Time: O(n / CHUNKSIZE + m / CHUNKSIZE + min(n,m)).
    int StrCompare(const LString& T) const noexcept;

    // 连接 S1 和 S2 并保存到当前串 / Concatenate S1 and S2 into this string. Time: O(n + m).
    bool Concat(const LString& S1, const LString& S2);

    // 清空当前串并释放空间 / Clear this string and release storage. Time: O(n / CHUNKSIZE).
    void ClearString() noexcept;

    // 查找子串 T，返回首次出现的位序 / Find the first occurrence of T. Time: O(n + m).
    int Index(const LString& T, int pos = 1) const;

    // 将当前串中不重叠的 T 替换为 V / Replace non-overlapping occurrences of T with V. Time: O(n + m + result length).
    bool Replace(const LString& T, const LString& V);

    // 判断当前串是否为空 / Check whether this string is empty. Time: O(1).
    bool StrEmpty() const noexcept;

    // 在第 pos 个字符之前插入 T / Insert T before position pos. Time: O(n + m).
    bool StrInsert(int pos, const LString& T);

    // 删除从第 pos 个字符开始的 len 个字符 / Delete len characters from position pos. Time: O(n).
    bool StrDelete(int pos, int len);

    // 销毁当前串的内容 / Destroy this string's contents. Time: O(n / CHUNKSIZE).
    void DestroyString() noexcept;

    // 读取指定字符 / Read a character at position pos. Time: O(n / CHUNKSIZE).
    bool GetChar(int pos, char& value) const noexcept;
};

}  // namespace dscpp

#endif  // DSCPP_LSTRING_H
