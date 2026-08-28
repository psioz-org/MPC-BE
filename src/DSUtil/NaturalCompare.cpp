#include "stdafx.h" // Assuming stdafx.h is needed for precompiled headers
#include "NaturalCompare.h"
#include <string>
#include <cctype>
#include <cwctype>
#include <algorithm>

static void SplitPathParts(const std::wstring& fullPath,
                           std::wstring& base,
                           std::wstring& ext)
{
    size_t sep = fullPath.find_last_of(L"\\/");
    size_t nameStart = (sep == std::wstring::npos) ? 0 : (sep + 1);
    std::wstring dir = (sep == std::wstring::npos) ? L"" : fullPath.substr(0, sep);
    std::wstring filename = fullPath.substr(nameStart);

    size_t dotInName = filename.rfind(L'.');
    bool hasDot = (dotInName != std::wstring::npos);

    std::wstring nameNoExt = hasDot ? filename.substr(0, dotInName) : filename;
    ext = hasDot ? filename.substr(dotInName + 1) : L"";

    base = dir.empty() ? nameNoExt : dir + L'\\' + nameNoExt;
}

int NaturalCompare(const std::wstring& aPath, const std::wstring& bPath) {
    // Helper to detect separators
    auto isSeparator = [](wchar_t c) { return c == L'\\' || c == L'/'; };

    std::wstring baseA, extA;
    std::wstring baseB, extB;
    SplitPathParts(aPath, baseA, extA);
    SplitPathParts(bPath, baseB, extB);

    // --- Compare base names naturally ---
    size_t i = 0, j = 0;
    while (i < baseA.size() && j < baseB.size()) {
        if (std::iswdigit(baseA[i]) && std::iswdigit(baseB[j])) {
            // Extract full numbers
            size_t ni = i;
            while (ni < baseA.size() && std::iswdigit(baseA[ni])) ni++;
            size_t nj = j;
            while (nj < baseB.size() && std::iswdigit(baseB[nj])) nj++;

            long long numA = std::stoll(baseA.substr(i, ni - i));
            long long numB = std::stoll(baseB.substr(j, nj - j));

            if (numA != numB)
                return numA < numB ? -1 : 1;

            i = ni;
            j = nj;
        } else if (std::iswdigit(baseA[i]) != std::iswdigit(baseB[j])) {
            // Only one is digit → put digits *after* letters
            return std::iswdigit(baseA[i]) ? 1 : -1;
        } else {
            // Handle separators
            if (isSeparator(baseA[i]) && isSeparator(baseB[j])) { ++i; ++j; continue; }
            if (isSeparator(baseA[i])) return -1;
            if (isSeparator(baseB[j])) return 1;

            wchar_t ca = std::towlower(baseA[i]);
            wchar_t cb = std::towlower(baseB[j]);
            if (ca != cb) return ca < cb ? -1 : 1;

            ++i; ++j;
        }
    }

    // If one base is prefix of the other, shorter base comes first
    if (i < baseA.size()) return 1;  // baseB ended first
    if (j < baseB.size()) return -1; // baseA ended first

    // --- Base names equal, compare extensions naturally ---
    if (!extA.empty() || !extB.empty()) {
	    int extCmp = NaturalCompare(extA, extB);
	    if (extCmp != 0) return extCmp;
	}

    // --- Base + extension equal ignoring case → final case-sensitive tie-break ---
    int cmp = aPath.compare(bPath);
    if (cmp != 0) return cmp < 0 ? -1 : 1;
    return 0;
}