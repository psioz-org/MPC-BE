#pragma once

#include <string>
#include <atlstr.h> // Required for CString

// Compare two wide strings in "natural" order like StrCmpLogicalW
int NaturalCompare(const std::wstring& a, const std::wstring& b);

// Overload for LPCWSTR
inline int NaturalCompare(LPCWSTR a, LPCWSTR b)
{
    return NaturalCompare(std::wstring(a), std::wstring(b));
}

// Overload for CString
inline int NaturalCompare(const CString& a, const CString& b)
{
    return NaturalCompare(a.GetString(), b.GetString());
}
