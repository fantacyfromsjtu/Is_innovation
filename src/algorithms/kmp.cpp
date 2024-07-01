#include "kmp.h"
#include <vector>
// KMP算法

//  计算部分匹配表
void computeLPSArray(const std::string &pattern, std::vector<int> &lps)
{
    int m = pattern.size();
    int len = 0;
    lps[0] = 0;
    int i = 1; // 从第2个字符开始匹配
    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            // 匹配成功
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
            else
            {
                lps[i] = lps[len - 1];
            }
        }
    }
}
bool kmpMatch(const std::string &pattern, const std::string &text)
{
    int m = pattern.size();
    int n = text.size();
    if (m == 0)
        return false;

    std::vector<int> lps(m, 0);
    computeLPSArray(pattern, lps); // 计算lps数组

    int i = 0; // index for text[]
    int j = 0; // index for pattern[]

    while (i < n)
    {
        if (j == m)
        {
            // 匹配成功
            return true;
        }
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            if (j == 0)
            {
                i++;
            }
            else
            {
                j = lps[j - 1];
            }
        }
    }
    return false;
}
