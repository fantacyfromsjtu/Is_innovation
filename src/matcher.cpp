#include "matcher.h"
#include "algorithms/brute_force.h"
#include "algorithms/kmp.h"
#include "algorithms/boyer_moore.h"
#include <iostream>

// 匹配算法调度函数
bool matchPattern(const AttackPattern &pattern, const std::string &text, MatchAlgorithm algorithm)
{
    switch (algorithm)
    {
    case MatchAlgorithm::BruteForce:
        // 使用暴力匹配算法
        return bruteForceMatch(pattern.patterncontent, text);
    case MatchAlgorithm::KMP:
        // 使用Knuth-Morris-Pratt算法
        return kmpMatch(pattern.patterncontent, text);
    case MatchAlgorithm::BoyerMoore:
        // 使用Boyer-Moore算法
        return boyerMooreMatch(pattern.patterncontent, text);
    default:
        return false;
    }
}
