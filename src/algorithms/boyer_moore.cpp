#include "boyer_moore.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

// 预处理坏字符表
void preprocessBadCharacter(const std::string &pattern, std::unordered_map<char, int> &badCharTable)
{
    int m = pattern.size();
    for (int i = 0; i < m - 1; ++i)
    {
        badCharTable[pattern[i]] = i;
    }
}

// 预处理好后缀表
void preprocessGoodSuffix(const std::string &pattern, std::vector<int> &goodSuffixTable, std::vector<int> &borderPosition)
{
    int m = pattern.size();
    int i = m, j = m + 1;
    borderPosition[i] = j;

    // 计算 borderPosition 数组
    while (i > 0)
    {
        while (j <= m && pattern[i - 1] != pattern[j - 1])
        {
            if (goodSuffixTable[j] == 0)
            {
                goodSuffixTable[j] = j - i;
            }
            j = borderPosition[j];
        }
        i--;
        j--;
        borderPosition[i] = j;
    }

    // 计算 goodSuffixTable 数组
    j = borderPosition[0];
    for (i = 0; i <= m; ++i)
    {
        if (goodSuffixTable[i] == 0)
        {
            goodSuffixTable[i] = j;
        }
        if (i == j)
        {
            j = borderPosition[j];
        }
    }
}

// Boyer-Moore 字符串匹配算法
bool boyerMooreMatch(const std::string &pattern, const std::string &text)
{
    int m = pattern.size();
    int n = text.size();
    if (m == 0)
        return false;

    // 构建坏字符表
    std::unordered_map<char, int> badCharTable;
    preprocessBadCharacter(pattern, badCharTable);

    // 构建好后缀表
    std::vector<int> goodSuffixTable(m + 1, 0);
    std::vector<int> borderPosition(m + 1, 0);
    preprocessGoodSuffix(pattern, goodSuffixTable, borderPosition);

    int s = 0; // 模式字符串与主字符串对齐的起始位置
    while (s <= n - m)
    {
        int j = m - 1;

        // 从后向前匹配
        while (j >= 0 && pattern[j] == text[s + j])
        {
            j--;
        }

        // 如果模式字符串完全匹配
        if (j < 0)
        {
            return true;
            // 移动模式字符串以便进行下一次匹配
            s += goodSuffixTable[0];
        }
        else
        {
            // 根据坏字符规则和好后缀规则移动模式字符串
            int badCharShift = j - (badCharTable.find(text[s + j]) != badCharTable.end() ? badCharTable[text[s + j]] : -1);
            int goodSuffixShift = goodSuffixTable[j + 1];
            s += std::max(badCharShift, goodSuffixShift);
        }
    }

    return false;
}
