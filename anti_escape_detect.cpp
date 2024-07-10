#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// 计算两个字符串之间的Levenshtein距离
int levenshtein_distance(const std::string& s1, const std::string& s2) {
    const size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

    for (size_t i = 0; i <= len1; ++i) d[i][0] = i;
    for (size_t i = 0; i <= len2; ++i) d[0][i] = i;

    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            d[i][j] = std::min({
                d[i - 1][j] + 1,      // 删除
                d[i][j - 1] + 1,      // 插入
                d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) // 替换
                });
        }
    }

    return d[len1][len2];
}

// 暴力匹配算法
std::vector<int> brute_force_search(const std::string& text, const std::string& pattern) {
    std::vector<int> matches;
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; ++i) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            matches.push_back(i);
        }
    }

    return matches;
}

// Levenshtein距离算法函数在这里假设已实现
// levenshtein_distance

std::vector<int> approximate_search(const std::string& text, const std::string& pattern, int max_distance) {
    std::vector<int> approximate_matches;
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; ++i) {
        std::string substring = text.substr(i, m);
        int distance = levenshtein_distance(substring, pattern);
        if (distance <= max_distance) {
            approximate_matches.push_back(i);
        }
    }

    return approximate_matches;
}

bool detect() {
    std::string text = "This is a simple example to demonstrate the combined algorithm for pattern matching.";
    std::string pattern = "simp1e"; // deliberately misspelled
    int max_distance = 2; // Maximum Levenshtein distance for approximate matches

    std::vector<int> matches = approximate_search(text, pattern, max_distance);
    
    if (!matches.empty())
    {
        std::cout << "Find “" << pattern << "” in text: “" << text <<"”"<< std::endl;
        return 1;
    }
    return 0;
}
