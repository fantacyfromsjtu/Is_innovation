#include "boyer_moore.h"
#include <vector>

// Boyer-Moore 算法实现
void preprocessBadChar(const std::string &pattern, std::vector<int> &badChar)
{
    int m = pattern.size();
    for (int i = 0; i < 256; ++i)
        badChar[i] = -1;
    for (int i = 0; i < m; ++i)
        badChar[(int)pattern[i]] = i;
}

bool boyerMooreMatch(const std::string &pattern, const std::string &text)
{
    int m = pattern.size();
    int n = text.size();
    std::vector<int> badChar(256);

    preprocessBadChar(pattern, badChar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0)
        {
            return true;
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        }
        else
            s += std::max(1, j - badChar[text[s + j]]);
    }
    return false;
}
