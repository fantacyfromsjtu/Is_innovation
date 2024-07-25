#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// 计算两个字符串之间的Levenshtein距离
int levenshtein_distance(const std::string& s1, const std::string& s2) {
    const size_t len1 = s1.size(), len2 = s2.size();
    // 创建二维数组存储计算结果
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    // 初始化边界条件
    for (size_t i = 0; i <= len1; ++i) d[i][0] = i; // 将第一列初始化为递增的值
    for (size_t i = 0; i <= len2; ++i) d[0][i] = i; // 将第一行初始化为递增的值

    // 填充二维数组
    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            // 计算插入、删除和替换的最小代价
            d[i][j] = std::min({
                d[i - 1][j] + 1,      // 删除
                d[i][j - 1] + 1,      // 插入
                d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) // 替换
                });
        }
    }

    // 返回Levenshtein距离
    return d[len1][len2];
}

// 暴力匹配算法
std::vector<int> brute_force_search(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    int n = text.length();
    int m = pattern.length();

    // 遍历文本的每一个子串
    for (int i = 0; i <= n - m; ++i) {
        int j = 0;
        // 比较子串和模式串是否匹配
        while (j < m && text[i + j] == pattern[j]) {
            ++j;
        }
        // 如果匹配成功，记录匹配的位置
        if (j == m) {
            matches.push_back(i);
        }
    }

    // 返回所有匹配的位置
    return matches;
}

// 使用Levenshtein距离的近似匹配算法
std::vector<int> approximate_search(const std::string& text, const std::string& pattern, int max_distance) {
    std::vector<int> approximate_matches;
    int n = text.length();
    int m = pattern.length();

    // 遍历文本的每一个子串
    for (int i = 0; i <= n - m; ++i) {
        std::string substring = text.substr(i, m); // 获取子串
        int distance = levenshtein_distance(substring, pattern); // 计算子串和模式串的Levenshtein距离
        if (distance <= max_distance) { // 如果距离在允许范围内，记录匹配的位置
            approximate_matches.push_back(i);
        }
    }

    // 返回所有近似匹配的位置
    return approximate_matches;
}

// 检测函数，判断模式串是否在文本中出现
bool detect(const std::string& text, const std::string& pattern, int max_distance) {
    std::vector<int> matches = approximate_search(text, pattern, max_distance); // 获取所有近似匹配的位置
    
    if (!matches.empty()) {
        // 如果找到匹配，输出匹配信息
        std::cout << "Find “" << pattern << "” in text: “" << text << "”" << std::endl;
        return true;
    }
    return false;
}

