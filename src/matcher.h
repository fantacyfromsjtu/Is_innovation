#ifndef MATCHER_H
#define MATCHER_H

#include "pattern_reader.h"
#include <string>

// 匹配算法枚举
enum class MatchAlgorithm
{
    BruteForce, // 暴力匹配算法
    KMP,        // Knuth-Morris-Pratt 算法
    BoyerMoore  // Boyer-Moore 算法
};

// 函数声明：匹配模式和文本，使用指定的算法
bool matchPattern(const AttackPattern &pattern, const std::string &text, MatchAlgorithm algorithm);

#endif // MATCHER_H
