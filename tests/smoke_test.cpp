// SPDX-FileCopyrightText: 2026 Eidric
// SPDX-License-Identifier: AGPL-3.0-only

#if defined(_MSVC_LANG)
static_assert(_MSVC_LANG >= 201703L, "C++17 is required");
#else
static_assert(__cplusplus >= 201703L, "C++17 is required");
#endif

int main() {
    return 0;
}
