#ifndef MATCHER_H
#define MATCHER_H

#include "pattern_reader.h"
#include <string>

// 匹配算法枚举
enum class MatchAlgorithm
{
    BruteForce,
    KMP,
    BoyerMoore
};

// 函数声明
bool matchPattern(const AttackPattern &pattern, const std::string &text, MatchAlgorithm algorithm);

#endif // MATCHER_H
