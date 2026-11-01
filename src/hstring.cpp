// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#include "../include/hstring.h"

#include <climits>
#include <new>
#include <utility>
#include <vector>

namespace dscpp {

// 释放内部存储空间 / Release internal storage. Time: O(1).
void HString::Release() noexcept {
    delete[] data.ch;
    data.ch = nullptr;
    data.length = 0;
}

// 检查位序是否合法 / Check whether a position is valid. Time: O(1).
bool HString::ValidPosition(int pos, bool allowEnd) const noexcept {
    if (allowEnd) {
        return pos >= 1 && pos <= data.length + 1;
    }

    return pos >= 1 && pos <= data.length;
}

// 深拷贝构造 / Deep-copy construction. Time: O(n).
HString::HString(const HString& other) {
    if (other.data.length == 0) {
        return;
    }

    data.ch = new char[other.data.length];

    for (int i = 0; i < other.data.length; i ++) {
        data.ch[i] = other.data.ch[i];
    }

    data.length = other.data.length;
}

// 深拷贝赋值 / Deep-copy assignment. Time: O(n).
HString& HString::operator=(const HString& other) {
    if (this == &other) {
        return *this;
    }

    char* newCh = nullptr;

    if (other.data.length > 0) {
        newCh = new char[other.data.length];

        for (int i = 0; i < other.data.length; i ++) {
            newCh[i] = other.data.ch[i];
        }
    }

    delete[] data.ch;

    data.ch = newCh;
    data.length = other.data.length;

    return *this;
}

// 移动构造 / Move construction. Time: O(1).
HString::HString(HString&& other) noexcept {
    data.ch = other.data.ch;
    data.length = other.data.length;

    other.data.ch = nullptr;
    other.data.length = 0;
}

// 移动赋值 / Move assignment. Time: O(1).
HString& HString::operator=(HString&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Release();

    data.ch = other.data.ch;
    data.length = other.data.length;

    other.data.ch = nullptr;
    other.data.length = 0;

    return *this;
}

// 释放动态存储空间 / Release dynamic storage. Time: O(1).
HString::~HString() {
    Release();
}

// 将 C 字符串赋给当前串 / Assign a C string. Time: O(n).
bool HString::StrAssign(const char* chars) {
    if (chars == nullptr) {
        return false;
    }

    int len = 0;

    while (chars[len] != '\0') {
        if (len == INT_MAX) {
            return false;
        }

        len ++;
    }

    char* newCh = nullptr;

    if (len > 0) {
        newCh = new char[len];

        for (int i = 0; i < len; i ++) {
            newCh[i] = chars[i];
        }
    }

    Release();
    data.ch = newCh;
    data.length = len;

    return true;
}

// 将串 S 复制到当前串 / Copy string S to this string. Time: O(n).
bool HString::StrCopy(const HString& S) {
    *this = S;
    return true;
}

// 获取串长 / Get string length. Time: O(1).
int HString::StrLength() const noexcept {
    return data.length;
}

// 获取子串并保存到当前串 / Extract a substring into this string. Time: O(len).
bool HString::SubString(const HString& S, int pos, int len) {
    if (pos < 1 || pos > S.data.length + 1 ||
        len < 0 || len > S.data.length - pos + 1) {
        return false;
    }

    HString result;

    if (len > 0) {
        result.data.ch = new char[len];

        for (int i = 0; i < len; i ++) {
            result.data.ch[i] = S.data.ch[pos + i - 1];
        }
    }

    result.data.length = len;
    *this = std::move(result);

    return true;
}

// 按字典序比较当前串与 T / Compare this string with T lexicographically. Time: O(min(n,m)).
int HString::StrCompare(const HString& T) const noexcept {
    int minLength = data.length < T.data.length ? data.length : T.data.length;

    for (int i = 0; i < minLength; i ++) {
        unsigned char a = static_cast<unsigned char>(data.ch[i]);
        unsigned char b = static_cast<unsigned char>(T.data.ch[i]);

        if (a != b) {
            return a < b ? -1 : 1;
        }
    }

    if (data.length < T.data.length) {
        return -1;
    }

    if (data.length > T.data.length) {
        return 1;
    }

    return 0;
}

// 连接 S1 和 S2 并保存到当前串 / Concatenate S1 and S2 into this string. Time: O(n + m).
bool HString::Concat(const HString& S1, const HString& S2) {
    if (S2.data.length > INT_MAX - S1.data.length) {
        return false;
    }

    int len = S1.data.length + S2.data.length;
    HString result;

    if (len > 0) {
        result.data.ch = new char[len];
    }

    result.data.length = len;

    for (int i = 0; i < S1.data.length; i ++) {
        result.data.ch[i] = S1.data.ch[i];
    }

    for (int i = 0; i < S2.data.length; i ++) {
        result.data.ch[S1.data.length + i] = S2.data.ch[i];
    }

    *this = std::move(result);
    return true;
}

// 清空当前串并释放空间 / Clear this string and release storage. Time: O(1).
void HString::ClearString() noexcept {
    Release();
}

// 查找子串 T，返回首次出现的位序 / Find the first occurrence of T. Time: O(nm).
int HString::Index(const HString& T, int pos) const noexcept {
    if (pos < 1 || pos > data.length || T.data.length == 0) {
        return 0;
    }

    for (int i = pos - 1; i <= data.length - T.data.length; i ++) {
        int j = 0;

        while (j < T.data.length && data.ch[i + j] == T.data.ch[j]) {
            j ++;
        }

        if (j == T.data.length) {
            return i + 1;
        }
    }

    return 0;
}

// 构造 KMP next 数组 / Build the KMP prefix table. Time: O(m).
void HString::GetNext(const HString& T, int* next) {
    if (T.data.length == 0) {
        return;
    }

    next[0] = 0;
    int j = 0;

    for (int i = 1; i < T.data.length; i ++) {
        while (j > 0 && T.data.ch[i] != T.data.ch[j]) {
            j = next[j - 1];
        }

        if (T.data.ch[i] == T.data.ch[j]) {
            j ++;
        }

        next[i] = j;
    }
}

// 将当前串中不重叠的 T 替换为 V / Replace non-overlapping occurrences of T with V. Time: O(n + m + k).
bool HString::Replace(const HString& T, const HString& V) {
    if (T.data.length == 0) {
        return false;
    }

    if (data.length == 0) {
        return true;
    }

    std::vector<int> next(T.data.length);
    std::vector<int> positions;

    GetNext(T, next.data());

    int j = 0;

    for (int i = 0; i < data.length; i ++) {
        while (j > 0 && data.ch[i] != T.data.ch[j]) {
            j = next[j - 1];
        }

        if (data.ch[i] == T.data.ch[j]) {
            j ++;
        }

        if (j == T.data.length) {
            positions.push_back(i - T.data.length + 1);
            j = 0;
        }
    }

    if (positions.empty()) {
        return true;
    }

    long long newLength = static_cast<long long>(data.length) +
        static_cast<long long>(positions.size()) * (V.data.length - T.data.length);

    if (newLength < 0 || newLength > INT_MAX) {
        return false;
    }

    HString result;
    result.data.length = static_cast<int>(newLength);

    if (result.data.length > 0) {
        result.data.ch = new char[result.data.length];
    }

    int source = 0;
    int target = 0;

    for (int pos : positions) {
        while (source < pos) {
            result.data.ch[target ++] = data.ch[source ++];
        }

        for (int i = 0; i < V.data.length; i ++) {
            result.data.ch[target ++] = V.data.ch[i];
        }

        source += T.data.length;
    }

    while (source < data.length) {
        result.data.ch[target ++] = data.ch[source ++];
    }

    *this = std::move(result);
    return true;
}

// 判断当前串是否为空 / Check whether this string is empty. Time: O(1).
bool HString::StrEmpty() const noexcept {
    return data.length == 0;
}

// 在第 pos 个字符之前插入 T / Insert T before position pos. Time: O(n + m).
bool HString::StrInsert(int pos, const HString& T) {
    if (!ValidPosition(pos, true) ||
        T.data.length > INT_MAX - data.length) {
        return false;
    }

    if (T.data.length == 0) {
        return true;
    }

    int newLength = data.length + T.data.length;
    HString result;

    result.data.ch = new char[newLength];
    result.data.length = newLength;

    int target = 0;

    for (int i = 0; i < pos - 1; i ++) {
        result.data.ch[target ++] = data.ch[i];
    }

    for (int i = 0; i < T.data.length; i ++) {
        result.data.ch[target ++] = T.data.ch[i];
    }

    for (int i = pos - 1; i < data.length; i ++) {
        result.data.ch[target ++] = data.ch[i];
    }

    *this = std::move(result);
    return true;
}

// 删除从第 pos 个字符开始的 len 个字符 / Delete len characters from position pos. Time: O(n).
bool HString::StrDelete(int pos, int len) {
    if (pos < 1 || pos > data.length + 1 ||
        len < 0 || len > data.length - pos + 1) {
        return false;
    }

    if (len == 0) {
        return true;
    }

    int newLength = data.length - len;
    HString result;

    if (newLength > 0) {
        result.data.ch = new char[newLength];
    }

    result.data.length = newLength;

    int target = 0;

    for (int i = 0; i < pos - 1; i ++) {
        result.data.ch[target ++] = data.ch[i];
    }

    for (int i = pos - 1 + len; i < data.length; i ++) {
        result.data.ch[target ++] = data.ch[i];
    }

    *this = std::move(result);
    return true;
}

// 销毁当前串的内容 / Destroy this string's contents. Time: O(1).
void HString::DestroyString() noexcept {
    ClearString();
}

// 读取指定字符 / Read a character at position pos. Time: O(1).
bool HString::GetChar(int pos, char& value) const noexcept {
    if (!ValidPosition(pos)) {
        return false;
    }

    value = data.ch[pos - 1];
    return true;
}

}  // namespace dscpp
