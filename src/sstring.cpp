// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#include "../include/sstring.h"

namespace dscpp {

// 获取实际串长 / Get the current string length. Time: O(1).
int SString::Length() const noexcept {
    return data.elem[0];
}

// 检查位序是否合法 / Check whether a position is valid. Time: O(1).
bool SString::ValidPosition(int pos, bool allowEnd) const noexcept {
    int length = Length();

    if (allowEnd) {
        return pos >= 1 && pos <= length + 1;
    }

    return pos >= 1 && pos <= length;
}

// 将 C 字符串赋给顺序串，超长时截断 / Assign a C string, truncating if necessary. Time: O(n).
bool SString::StrAssign(const char* chars) {
    if (chars == nullptr) {
        return false;
    }

    SStringData result;
    int len = 0;

    while (chars[len] != '\0' && len < MAXSTRLEN) {
        result.elem[len + 1] = static_cast<unsigned char>(chars[len]);
        len ++;
    }

    result.elem[0] = static_cast<unsigned char>(len);
    data = result;

    return true;
}

// 将串 S 复制到当前串 / Copy string S to this string. Time: O(n).
bool SString::StrCopy(const SString& S) {
    data = S.data;
    return true;
}

// 获取串长 / Get string length. Time: O(1).
int SString::StrLength() const noexcept {
    return Length();
}

// 获取子串并保存到当前串 / Extract a substring into this string. Time: O(len).
bool SString::SubString(const SString& S, int pos, int len) {
    int sLength = S.Length();

    if (pos < 1 || pos > sLength + 1 ||
        len < 0 || len > sLength - pos + 1) {
        return false;
    }

    SStringData result;

    for (int i = 1; i <= len; i ++) {
        result.elem[i] = S.data.elem[pos + i - 1];
    }

    result.elem[0] = static_cast<unsigned char>(len);
    data = result;

    return true;
}

// 按字典序比较当前串与 T / Compare this string with T lexicographically. Time: O(min(n,m)).
int SString::StrCompare(const SString& T) const noexcept {
    int sLength = Length();
    int tLength = T.Length();
    int minLength = sLength < tLength ? sLength : tLength;

    for (int i = 1; i <= minLength; i ++) {
        if (data.elem[i] != T.data.elem[i]) {
            return static_cast<int>(data.elem[i]) - static_cast<int>(T.data.elem[i]);
        }
    }

    return sLength - tLength;
}

// 连接 S1 和 S2 并保存到当前串，超长时截断 / Concatenate S1 and S2, truncating if necessary. Time: O(n + m).
bool SString::Concat(const SString& S1, const SString& S2) {
    SStringData result;
    int len = 0;

    for (int i = 1; i <= S1.Length() && len < MAXSTRLEN; i ++) {
        result.elem[++len] = S1.data.elem[i];
    }

    for (int i = 1; i <= S2.Length() && len < MAXSTRLEN; i ++) {
        result.elem[++len] = S2.data.elem[i];
    }

    result.elem[0] = static_cast<unsigned char>(len);
    data = result;

    return len == S1.Length() + S2.Length();
}

// 清空当前串 / Clear this string. Time: O(1).
void SString::ClearString() noexcept {
    data.elem[0] = 0;
}

// 查找子串 T，返回首次出现的位序 / Find the first occurrence of T. Time: O(nm).
int SString::Index(const SString& T, int pos) const noexcept {
    int sLength = Length();
    int tLength = T.Length();

    if (pos < 1 || pos > sLength + 1 || tLength == 0) {
        return 0;
    }

    for (int i = pos; i <= sLength - tLength + 1; i ++) {
        int j = 1;

        while (j <= tLength && data.elem[i + j - 1] == T.data.elem[j]) {
            j ++;
        }

        if (j > tLength) {
            return i;
        }
    }

    return 0;
}

// 将当前串中不重叠的 T 替换为 V / Replace non-overlapping occurrences of T with V. Time: O(n + k*m).
bool SString::Replace(const SString& T, const SString& V) {
    int tLength = T.Length();
    int sLength = Length();

    if (tLength == 0) {
        return false;
    }

    SStringData result;
    int source = 1;
    int target = 0;

    while (source <= sLength) {
        bool matched = source + tLength - 1 <= sLength;

        for (int j = 1; matched && j <= tLength; j ++) {
            if (data.elem[source + j - 1] != T.data.elem[j]) {
                matched = false;
            }
        }

        if (matched) {
            for (int j = 1; j <= V.Length() && target < MAXSTRLEN; j ++) {
                result.elem[++target] = V.data.elem[j];
            }

            source += tLength;
        }
        else {
            if (target < MAXSTRLEN) {
                result.elem[++target] = data.elem[source];
            }

            source ++;
        }
    }

    result.elem[0] = static_cast<unsigned char>(target);
    data = result;

    return true;
}

// 判断当前串是否为空 / Check whether this string is empty. Time: O(1).
bool SString::StrEmpty() const noexcept {
    return Length() == 0;
}

// 在第 pos 个字符之前插入 T / Insert T before position pos. Time: O(n + m).
bool SString::StrInsert(int pos, const SString& T) {
    int sLength = Length();
    int tLength = T.Length();

    if (!ValidPosition(pos, true) || sLength + tLength > MAXSTRLEN) {
        return false;
    }

    SStringData result;
    int target = 0;

    for (int i = 1; i < pos; i ++) {
        result.elem[++target] = data.elem[i];
    }

    for (int i = 1; i <= tLength; i ++) {
        result.elem[++target] = T.data.elem[i];
    }

    for (int i = pos; i <= sLength; i ++) {
        result.elem[++target] = data.elem[i];
    }

    result.elem[0] = static_cast<unsigned char>(target);
    data = result;

    return true;
}

// 删除从第 pos 个字符开始的 len 个字符 / Delete len characters from position pos. Time: O(n).
bool SString::StrDelete(int pos, int len) {
    int sLength = Length();

    if (pos < 1 || pos > sLength + 1 ||
        len < 0 || len > sLength - pos + 1) {
        return false;
    }

    SStringData result;
    int target = 0;

    for (int i = 1; i < pos; i ++) {
        result.elem[++target] = data.elem[i];
    }

    for (int i = pos + len; i <= sLength; i ++) {
        result.elem[++target] = data.elem[i];
    }

    result.elem[0] = static_cast<unsigned char>(target);
    data = result;

    return true;
}

// 销毁当前串的内容 / Destroy the string contents. Time: O(1).
void SString::DestroyString() noexcept {
    ClearString();
}

// 读取指定字符 / Read a character at position pos. Time: O(1).
bool SString::GetChar(int pos, char& value) const noexcept {
    if (!ValidPosition(pos)) {
        return false;
    }

    value = static_cast<char>(data.elem[pos]);
    return true;
}

}  // namespace dscpp
