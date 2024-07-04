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
        //std::cout << "call BF\n";
        return bruteForceMatch(pattern.patterncontent, text);
    case MatchAlgorithm::KMP:
        //std::cout << "call KMP\n";
        return kmpMatch(pattern.patterncontent, text);
    case MatchAlgorithm::BoyerMoore:
        //std::cout << "call BM\n";
        return boyerMooreMatch(pattern.patterncontent, text);
    default:
        return false;
    }
}
