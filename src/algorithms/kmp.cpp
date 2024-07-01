#include "kmp.h"
#include <vector>

void computeLPSArray(const std::string &pattern, std::vector<int> &lps)
{
    int length = 0;
    lps[0] = 0; // lps[0] is always 0

    int i = 1;
    while (i < pattern.size())
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

bool kmpMatch(const std::string &pattern, const std::string &text)
{
    if (pattern.empty())
        return false;

    int m = pattern.size();
    int n = text.size();

    std::vector<int> lps(m);
    computeLPSArray(pattern, lps);

    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            return true; // Found pattern
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return false;
}
