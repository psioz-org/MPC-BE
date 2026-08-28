#include "stdafx.h"
#include "NaturalCompare.h"
#include <string>
#include <cctype>
#include <cwctype>
#include <algorithm>
#include <unordered_map>
#include <climits>

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

static bool IsIgnoredSymbol(wchar_t c)
{
    return !std::iswalnum(c) && c != L'/' && c != L'\\';
}

static bool GetNumberWord(const std::wstring& word, int& value)
{
    static const std::unordered_map<std::wstring, int> numbers = {
        {L"zero", 0},
        {L"one", 1},
        {L"two", 2},
        {L"three", 3},
        {L"four", 4},
        {L"five", 5},
        {L"six", 6},
        {L"seven", 7},
        {L"eight", 8},
        {L"nine", 9},
        {L"ten", 10},
        {L"eleven", 11},
        {L"twelve", 12},
        {L"thirteen", 13},
        {L"fourteen", 14},
        {L"fifteen", 15},
        {L"sixteen", 16},
        {L"seventeen", 17},
        {L"eighteen", 18},
        {L"nineteen", 19},
        {L"twenty", 20},
        {L"thirty", 30},
        {L"forty", 40},
        {L"fifty", 50},
        {L"sixty", 60},
        {L"seventy", 70},
        {L"eighty", 80},
        {L"ninety", 90},
        {L"hundred", 100},
        {L"thousand", 1000},
        {L"million", 1000000},
        {L"billion", 1000000000}
    };

    auto it = numbers.find(word);

    if (it == numbers.end())
        return false;

    value = it->second;
    return true;
}

static bool GetOrdinalWord(const std::wstring& word, int& value)
{
    static const std::unordered_map<std::wstring, int> ordinals = {
        {L"zeroth", 0},
        {L"first", 1},
        {L"second", 2},
        {L"third", 3},
        {L"fourth", 4},
        {L"fifth", 5},
        {L"sixth", 6},
        {L"seventh", 7},
        {L"eighth", 8},
        {L"ninth", 9},
        {L"tenth", 10},
        {L"eleventh", 11},
        {L"twelfth", 12},
        {L"thirteenth", 13},
        {L"fourteenth", 14},
        {L"fifteenth", 15},
        {L"sixteenth", 16},
        {L"seventeenth", 17},
        {L"eighteenth", 18},
        {L"nineteenth", 19},
        {L"twentieth", 20},
        {L"thirtieth", 30},
        {L"fortieth", 40},
        {L"fiftieth", 50},
        {L"sixtieth", 60},
        {L"seventieth", 70},
        {L"eightieth", 80},
        {L"ninetieth", 90},
        {L"hundredth", 100},
        {L"thousandth", 1000},
        {L"millionth", 1000000},
        {L"billionth", 1000000000}
    };

    auto it = ordinals.find(word);

    if (it == ordinals.end())
        return false;

    value = it->second;
    return true;
}

struct NumericToken
{
    long long value;
    size_t end;
    int type;
};

static bool GetNumericToken(const std::wstring& s,
                            size_t start,
                            NumericToken& token)
{
    if (start >= s.size())
        return false;

    // Actual numeric digits.
    if (std::iswdigit(s[start])) {
        size_t end = start;

        while (end < s.size() && std::iswdigit(s[end]))
            ++end;

        long long value = 0;

        for (size_t i = start; i < end; ++i) {
            int digit = s[i] - L'0';

            if (value > (LLONG_MAX - digit) / 10) {
                value = LLONG_MAX;
                break;
            }

            value = value * 10 + digit;
        }

        token.value = value;
        token.end = end;
        token.type = 3; // Actual digits.
        return true;
    }

    if (!std::iswalpha(s[start]))
        return false;

    size_t pos = start;
    long long total = 0;
    long long current = 0;
    bool found = false;
    bool hasOrdinal = false;
    bool hasCardinal = false;

    while (pos < s.size()) {
        size_t wordEnd = pos;

        while (wordEnd < s.size() && std::iswalpha(s[wordEnd]))
            ++wordEnd;

        if (wordEnd == pos)
            break;

        std::wstring word = s.substr(pos, wordEnd - pos);

        for (wchar_t& c : word)
            c = std::towlower(c);

        int number = 0;

        if (GetOrdinalWord(word, number)) {
            hasOrdinal = true;
            found = true;

            // An ordinal at the end terminates the number.
            current += number;
            pos = wordEnd;
            break;
        }

        if (GetNumberWord(word, number)) {
            hasCardinal = true;
            found = true;

            if (number == 100) {
                if (current == 0)
                    current = 1;

                current *= 100;
            }
            else if (number == 1000) {
                if (current == 0)
                    current = 1;

                total += current * 1000;
                current = 0;
            }
            else if (number == 1000000) {
                if (current == 0)
                    current = 1;

                total += current * 1000000;
                current = 0;
            }
            else if (number == 1000000000) {
                if (current == 0)
                    current = 1;

                total += current * 1000000000;
                current = 0;
            }
            else {
                current += number;
            }

            pos = wordEnd;
        }
        else {
            break;
        }

        // Continue through a hyphen:
        // twenty-three, thirty-three, etc.
        if (pos < s.size() && s[pos] == L'-') {
            size_t next = pos + 1;

            if (next < s.size() && std::iswalpha(s[next])) {
                pos = next;
                continue;
            }
        }

        // Continue through a space only if the next word is another
        // number word. This allows "one hundred", "twenty one", etc.
        if (pos < s.size() && std::iswspace(s[pos])) {
            size_t next = pos + 1;

            while (next < s.size() && std::iswspace(s[next]))
                ++next;

            if (next < s.size() && std::iswalpha(s[next])) {
                std::wstring nextWord;
                size_t nextEnd = next;

                while (nextEnd < s.size() && std::iswalpha(s[nextEnd]))
                    ++nextEnd;

                nextWord = s.substr(next, nextEnd - next);

                for (wchar_t& c : nextWord)
                    c = std::towlower(c);

                int dummy = 0;

                if (GetNumberWord(nextWord, dummy) ||
                    GetOrdinalWord(nextWord, dummy)) {
                    pos = next;
                    continue;
                }
            }
        }

        break;
    }

    if (!found)
        return false;

    token.value = total + current;
    token.end = pos;

    // Equal numeric values:
    // ordinal word < cardinal word < actual digits
    token.type = hasOrdinal ? 1 : (hasCardinal ? 2 : 3);

    return true;
}

static int CompareNaturalPart(const std::wstring& a,
                              const std::wstring& b)
{
    size_t i = 0;
    size_t j = 0;

    while (true) {
        while (i < a.size() && IsIgnoredSymbol(a[i]))
            ++i;

        while (j < b.size() && IsIgnoredSymbol(b[j]))
            ++j;

        if (i >= a.size() || j >= b.size())
            break;

        NumericToken tokenA{};
        NumericToken tokenB{};

        bool numericA = GetNumericToken(a, i, tokenA);
        bool numericB = GetNumericToken(b, j, tokenB);

        // Both sides are numeric tokens.
        if (numericA && numericB) {
            if (tokenA.value != tokenB.value)
                return tokenA.value < tokenB.value ? -1 : 1;

            // Same numeric value:
            // ordinal word, cardinal word, actual digits.
            if (tokenA.type != tokenB.type)
                return tokenA.type < tokenB.type ? -1 : 1;

            i = tokenA.end;
            j = tokenB.end;
            continue;
        }

        // One side is numeric.
        if (numericA != numericB)
            return numericA ? -1 : 1;

        wchar_t ca = std::towlower(a[i]);
        wchar_t cb = std::towlower(b[j]);

        if (ca != cb)
            return ca < cb ? -1 : 1;

        ++i;
        ++j;
    }

    while (i < a.size() && IsIgnoredSymbol(a[i]))
        ++i;

    while (j < b.size() && IsIgnoredSymbol(b[j]))
        ++j;

    if (i < a.size())
        return 1;

    if (j < b.size())
        return -1;

    return 0;
}

int NaturalCompare(const std::wstring& aPath,
                   const std::wstring& bPath)
{
    std::wstring baseA, extA;
    std::wstring baseB, extB;

    SplitPathParts(aPath, baseA, extA);
    SplitPathParts(bPath, baseB, extB);

    // --- Compare base names naturally, ignoring symbols except path separators ---
    int cmp = CompareNaturalPart(baseA, baseB);

    if (cmp != 0)
        return cmp;

    // --- Normalized base names equal, compare original base names ---
    cmp = baseA.compare(baseB);

    if (cmp != 0)
        return cmp < 0 ? -1 : 1;

    // --- Base names equal, compare extensions naturally, ignoring symbols ---
    cmp = CompareNaturalPart(extA, extB);

    if (cmp != 0)
        return cmp;

    // --- Normalized extensions equal, compare original extensions ---
    cmp = extA.compare(extB);

    if (cmp != 0)
        return cmp < 0 ? -1 : 1;

    // --- Base + extension equal → final complete path tie-break ---
    cmp = aPath.compare(bPath);

    if (cmp != 0)
        return cmp < 0 ? -1 : 1;

    return 0;
}