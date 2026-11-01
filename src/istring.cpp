// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#include "../include/istring.h"

#include <climits>
#include <utility>
#include <vector>

namespace dscpp {

// 释放所有结点 / Release all nodes. Time: O(n / CHUNKSIZE).
void LString::Release() noexcept {
    Chunk* current = data.head;

    while (current != nullptr) {
        Chunk* next = current->next;
        delete current;
        current = next;
    }

    data.head = nullptr;
    data.tail = nullptr;
    data.curlen = 0;
}

// 向当前串尾部追加一个字符 / Append one character. Amortized time: O(1).
void LString::AppendChar(char value) {
    if (data.tail == nullptr || data.curlen % CHUNKSIZE == 0) {
        Chunk* newChunk = new Chunk{};

        if (data.tail == nullptr) {
            data.head = newChunk;
        }
        else {
            data.tail->next = newChunk;
        }

        data.tail = newChunk;
    }

    data.tail->ch[data.curlen % CHUNKSIZE] = value;
    data.curlen ++;
}

// 将 source 从 start 开始的 len 个字符追加到当前串 / Append a range from source. Time: O(len + n / CHUNKSIZE).
bool LString::AppendRange(const LString& source, int start, int len) {
    if (start < 0 || len < 0 ||
        start > source.data.curlen ||
        len > source.data.curlen - start) {
        return false;
    }

    if (len == 0) {
        return true;
    }

    const Chunk* current = source.data.head;
    int offset = start;

    while (current != nullptr && offset >= CHUNKSIZE) {
        current = current->next;
        offset -= CHUNKSIZE;
    }

    for (int i = 0; i < len; i ++) {
        if (current == nullptr) {
            return false;
        }

        AppendChar(current->ch[offset]);
        offset ++;

        if (offset == CHUNKSIZE) {
            current = current->next;
            offset = 0;
        }
    }

    return true;
}

// 将串内容复制到连续字符数组 / Copy string contents to a contiguous buffer. Time: O(n).
void LString::CopyTo(char* buffer) const noexcept {
    if (buffer == nullptr) {
        return;
    }

    const Chunk* current = data.head;
    int copied = 0;

    while (current != nullptr && copied < data.curlen) {
        int count = data.curlen - copied;

        if (count > CHUNKSIZE) {
            count = CHUNKSIZE;
        }

        for (int i = 0; i < count; i ++) {
            buffer[copied ++] = current->ch[i];
        }

        current = current->next;
    }
}

// 检查位序是否合法 / Check whether a position is valid. Time: O(1).
bool LString::ValidPosition(int pos, bool allowEnd) const noexcept {
    if (pos < 1) {
        return false;
    }

    if (allowEnd) {
        return pos - 1 <= data.curlen;
    }

    return pos <= data.curlen;
}

// 深拷贝构造 / Deep-copy construction. Time: O(n).
LString::LString(const LString& other) {
    try {
        AppendRange(other, 0, other.data.curlen);
    }
    catch (...) {
        Release();
        throw;
    }
}

// 深拷贝赋值 / Deep-copy assignment. Time: O(n).
LString& LString::operator=(const LString& other) {
    if (this == &other) {
        return *this;
    }

    LString result(other);
    *this = std::move(result);

    return *this;
}

// 移动构造 / Move construction. Time: O(1).
LString::LString(LString&& other) noexcept {
    data.head = other.data.head;
    data.tail = other.data.tail;
    data.curlen = other.data.curlen;

    other.data.head = nullptr;
    other.data.tail = nullptr;
    other.data.curlen = 0;
}

// 移动赋值 / Move assignment. Time: O(1).
LString& LString::operator=(LString&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Release();

    data.head = other.data.head;
    data.tail = other.data.tail;
    data.curlen = other.data.curlen;

    other.data.head = nullptr;
    other.data.tail = nullptr;
    other.data.curlen = 0;

    return *this;
}

// 释放所有结点 / Release all nodes. Time: O(n / CHUNKSIZE).
LString::~LString() {
    Release();
}

// 将 C 字符串赋给当前串 / Assign a C string. Time: O(n).
bool LString::StrAssign(const char* chars) {
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

    LString result;

    for (int i = 0; i < len; i ++) {
        result.AppendChar(chars[i]);
    }

    *this = std::move(result);
    return true;
}

// 将串 S 复制到当前串 / Copy string S to this string. Time: O(n).
bool LString::StrCopy(const LString& S) {
    *this = S;
    return true;
}

// 获取串长 / Get string length. Time: O(1).
int LString::StrLength() const noexcept {
    return data.curlen;
}

// 获取子串并保存到当前串 / Extract a substring into this string. Time: O(n + len).
bool LString::SubString(const LString& S, int pos, int len) {
    if (pos < 1 || pos - 1 > S.data.curlen ||
        len < 0 || len > S.data.curlen - (pos - 1)) {
        return false;
    }

    LString result;

    if (!result.AppendRange(S, pos - 1, len)) {
        return false;
    }

    *this = std::move(result);
    return true;
}

// 按字典序比较当前串与 T / Compare this string with T lexicographically.
int LString::StrCompare(const LString& T) const noexcept {
    const Chunk* sChunk = data.head;
    const Chunk* tChunk = T.data.head;
    int sOffset = 0;
    int tOffset = 0;
    int minLength = data.curlen < T.data.curlen ? data.curlen : T.data.curlen;

    for (int i = 0; i < minLength; i ++) {
        unsigned char a = static_cast<unsigned char>(sChunk->ch[sOffset]);
        unsigned char b = static_cast<unsigned char>(tChunk->ch[tOffset]);

        if (a != b) {
            return a < b ? -1 : 1;
        }

        sOffset ++;
        tOffset ++;

        if (sOffset == CHUNKSIZE) {
            sChunk = sChunk->next;
            sOffset = 0;
        }

        if (tOffset == CHUNKSIZE) {
            tChunk = tChunk->next;
            tOffset = 0;
        }
    }

    if (data.curlen < T.data.curlen) {
        return -1;
    }

    if (data.curlen > T.data.curlen) {
        return 1;
    }

    return 0;
}

// 连接 S1 和 S2 并保存到当前串 / Concatenate S1 and S2 into this string. Time: O(n + m).
bool LString::Concat(const LString& S1, const LString& S2) {
    if (S2.data.curlen > INT_MAX - S1.data.curlen) {
        return false;
    }

    LString result;

    result.AppendRange(S1, 0, S1.data.curlen);
    result.AppendRange(S2, 0, S2.data.curlen);

    *this = std::move(result);
    return true;
}

// 清空当前串并释放空间 / Clear this string and release storage. Time: O(n / CHUNKSIZE).
void LString::ClearString() noexcept {
    Release();
}

// 构造 KMP next 数组 / Build the KMP prefix table. Time: O(m).
void LString::GetNext(const char* pattern, int length, int* next) noexcept {
    if (length <= 0 || pattern == nullptr || next == nullptr) {
        return;
    }

    next[0] = 0;
    int j = 0;

    for (int i = 1; i < length; i ++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            j ++;
        }

        next[i] = j;
    }
}

// 查找子串 T，返回首次出现的位序 / Find the first occurrence of T. Time: O(n + m).
int LString::Index(const LString& T, int pos) const {
    if (T.data.curlen == 0 ||
        pos < 1 || pos - 1 > data.curlen) {
        return 0;
    }

    std::vector<char> text(data.curlen);
    std::vector<char> pattern(T.data.curlen);
    std::vector<int> next(T.data.curlen);

    CopyTo(text.data());
    T.CopyTo(pattern.data());
    GetNext(pattern.data(), T.data.curlen, next.data());

    int j = 0;

    for (int i = pos - 1; i < data.curlen; i ++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }

        if (text[i] == pattern[j]) {
            j ++;
        }

        if (j == T.data.curlen) {
            return i - T.data.curlen + 2;
        }
    }

    return 0;
}

// 将当前串中不重叠的 T 替换为 V / Replace non-overlapping occurrences of T with V.
bool LString::Replace(const LString& T, const LString& V) {
    if (T.data.curlen == 0) {
        return false;
    }

    if (data.curlen == 0) {
        return true;
    }

    std::vector<char> text(data.curlen);
    std::vector<char> pattern(T.data.curlen);
    std::vector<int> next(T.data.curlen);
    std::vector<int> positions;

    CopyTo(text.data());
    T.CopyTo(pattern.data());
    GetNext(pattern.data(), T.data.curlen, next.data());

    int j = 0;

    for (int i = 0; i < data.curlen; i ++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }

        if (text[i] == pattern[j]) {
            j ++;
        }

        if (j == T.data.curlen) {
            positions.push_back(i - T.data.curlen + 1);
            j = 0;
        }
    }

    if (positions.empty()) {
        return true;
    }

    long long newLength = static_cast<long long>(data.curlen) +
        static_cast<long long>(positions.size()) *
        (static_cast<long long>(V.data.curlen) - T.data.curlen);

    if (newLength < 0 || newLength > INT_MAX) {
        return false;
    }

    LString result;
    int source = 0;

    for (int pos : positions) {
        result.AppendRange(*this, source, pos - source);
        result.AppendRange(V, 0, V.data.curlen);
        source = pos + T.data.curlen;
    }

    result.AppendRange(*this, source, data.curlen - source);

    *this = std::move(result);
    return true;
}

// 判断当前串是否为空 / Check whether this string is empty. Time: O(1).
bool LString::StrEmpty() const noexcept {
    return data.curlen == 0;
}

// 在第 pos 个字符之前插入 T / Insert T before position pos. Time: O(n + m).
bool LString::StrInsert(int pos, const LString& T) {
    if (!ValidPosition(pos, true) ||
        T.data.curlen > INT_MAX - data.curlen) {
        return false;
    }

    if (T.data.curlen == 0) {
        return true;
    }

    LString result;

    result.AppendRange(*this, 0, pos - 1);
    result.AppendRange(T, 0, T.data.curlen);
    result.AppendRange(*this, pos - 1, data.curlen - (pos - 1));

    *this = std::move(result);
    return true;
}

// 删除从第 pos 个字符开始的 len 个字符 / Delete len characters from position pos. Time: O(n).
bool LString::StrDelete(int pos, int len) {
    if (pos < 1 || pos - 1 > data.curlen ||
        len < 0 || len > data.curlen - (pos - 1)) {
        return false;
    }

    if (len == 0) {
        return true;
    }

    LString result;

    result.AppendRange(*this, 0, pos - 1);
    result.AppendRange(*this, pos - 1 + len,
                       data.curlen - (pos - 1 + len));

    *this = std::move(result);
    return true;
}

// 销毁当前串的内容 / Destroy this string's contents. Time: O(n / CHUNKSIZE).
void LString::DestroyString() noexcept {
    ClearString();
}

// 读取指定字符 / Read a character at position pos. Time: O(n / CHUNKSIZE).
bool LString::GetChar(int pos, char& value) const noexcept {
    if (!ValidPosition(pos)) {
        return false;
    }

    int index = pos - 1;
    const Chunk* current = data.head;

    while (current != nullptr && index >= CHUNKSIZE) {
        current = current->next;
        index -= CHUNKSIZE;
    }

    if (current == nullptr) {
        return false;
    }

    value = current->ch[index];
    return true;
}

}  // namespace dscpp
