/*
 * Standalone test for NaturalCompare.
 * Compiles real src/DSUtil/NaturalCompare.cpp with stdafx.h stripped.
 */

#include "NaturalCompare.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

static std::wstring PadIndex(size_t i, size_t max) {
    std::wstring s = std::to_wstring(i);
    size_t width = 1;
    while (max > 9) { width++; max /= 10; }
    if (s.size() < width) s.insert(0, width - s.size(), L'0');
    return s;
}

static const char* g_input[] = {
    "D:\\repository\\MPC-BE\\test\\natural_compare\\10 Tenth\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Second.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\C - Third.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Seven.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\4.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Seventeen.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Eleven.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode_10.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\22.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\21.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\10 - Tenth.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\01 First\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Thirteen.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Twenty.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\16.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Two.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\file_c.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\b - Second.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\A First\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Ten.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\A - First.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\C Third\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\8.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Fifteen.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\b Second\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\1 - First.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\First.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode 2.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Hundred.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\02 Second\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Twenty-one.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Ninth.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode 10.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\14.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Third.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Nineteen.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Twenty*one.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Fifth.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\18.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode_01.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode 02.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\10 Episode\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode_2.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\2 - Second.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\file_a.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\1 Episode\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\file-b.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\02 - Second.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Six.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\2 Episode\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\01 - First.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode 01.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\12.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\file_B.mp4",
};

static const char* g_expected[] = {
    "D:\\repository\\MPC-BE\\test\\natural_compare\\First.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\01 - First.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\1 - First.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\01 First\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\1 Episode\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Second.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Two.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\02 - Second.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\2 - Second.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\02 Second\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\2 Episode\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Third.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\4.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Fifth.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Six.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Seven.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\8.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Ninth.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Ten.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\10 - Tenth.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\10 Tenth\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\10 Episode\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Eleven.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\12.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Thirteen.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\14.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Fifteen.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\16.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Seventeen.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\18.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Nineteen.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Twenty.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Twenty*one.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Twenty-one.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\21.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\22.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\Hundred.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\A - First.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\A First\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\b - Second.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\b Second\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\C - Third.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\C Third\\test.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode 01.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode_01.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode 02.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode 2.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode_2.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode 10.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\episode_10.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\file_a.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\file-b.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\file_B.mp4",
    "D:\\repository\\MPC-BE\\test\\natural_compare\\file_c.mp4",
};

int main() {
    std::vector<std::wstring> input;
    input.reserve(sizeof(g_input) / sizeof(g_input[0]));
    for (const auto* s : g_input) {
        input.emplace_back(s, s + strlen(s));
    }

    std::vector<std::wstring> expected;
    expected.reserve(sizeof(g_expected) / sizeof(g_expected[0]));
    for (const auto* s : g_expected) {
        expected.emplace_back(s, s + strlen(s));
    }

    std::vector<std::wstring> actual = input;
    std::sort(actual.begin(), actual.end(),
        [](const std::wstring& a, const std::wstring& b) {
            return NaturalCompare(a, b) < 0;
        });

    bool ok = true;
    if (actual.size() != expected.size()) {
        ok = false;
        std::wcout << L"SIZE MISMATCH: actual=" << actual.size()
                   << L", expected=" << expected.size() << L"\n";
    }

    std::vector<bool> mismatch(actual.size(), false);
    size_t n = actual.size() < expected.size() ? actual.size() : expected.size();
    for (size_t i = 0; i < n; ++i) {
        if (actual[i] != expected[i]) {
            ok = false;
            mismatch[i] = true;
            std::wcout << L"\x1b[33mDIFF at " << i << L": actual=\"" << actual[i]
                       << L"\" expected=\"" << expected[i] << L"\"\x1b[0m\n";
        }
    }

    if (ok) {
        std::wcout << L"PASS: sorted order matches expected\n";
    } else {
        std::wcout << L"FAIL: sorted order does not match\n";
        std::wcout << L"\nActual order:\n";
        for (size_t i = 0; i < actual.size(); ++i) {
            if (mismatch[i]) std::wcout << L"\x1b[33m";
            std::wcout << L" " << std::setfill(L'0') << std::setw(3) << i << L": \"" << actual[i] << L"\"";
            if (mismatch[i]) std::wcout << L"\x1b[0m";
            std::wcout << L"\n";
        }
        std::wcout << L"\nExpected order:\n";
        for (size_t i = 0; i < expected.size(); ++i) {
            if (mismatch[i]) std::wcout << L"\x1b[33m";
            std::wcout << L" " << std::setfill(L'0') << std::setw(3) << i << L": \"" << expected[i] << L"\"";
            if (mismatch[i]) std::wcout << L"\x1b[0m";
            std::wcout << L"\n";
        }
    }

    return ok ? 0 : 1;
}
