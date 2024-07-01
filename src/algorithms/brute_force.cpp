#include "brute_force.h"

bool bruteForceMatch(const std::string &pattern, const std::string &text)
{
    size_t m = pattern.size();
    size_t n = text.size();

    for (size_t i = 0; i <= n - m; ++i)
    {
        size_t j = 0;
        while (j < m && text[i + j] == pattern[j])
        {
            ++j;
        }
        if (j == m)
        {
            return true;
        }
    }
    return false;
}
