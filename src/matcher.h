/*
特征串匹配算法模块头文件
*/
#ifndef MATCHER_H
#define MATCHER_H

#include <string>
#include "pattern_reader.h"

// 匹配算法类型枚举
enum class MatchAlgorithm
{
    BruteForce,
    KMP,
    BoyerMoore
};

// 根据选择的算法匹配模式
bool matchPattern(const AttackPattern &pattern, const std::string &text, MatchAlgorithm algorithm);

#endif // MATCHER_H
