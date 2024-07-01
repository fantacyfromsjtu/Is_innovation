/*
特征串匹配算法模块
*/
#include "matcher.h"
#include "algorithms/brute_force.h"
#include "algorithms/kmp.h"
#include "algorithms/boyer_moore.h"

bool matchPattern(const AttackPattern &pattern, const std::string &text, MatchAlgorithm algorithm)
{
    switch (algorithm)
    {
    case MatchAlgorithm::BruteForce:
        return bruteForceMatch(pattern.patterncontent, text);
    case MatchAlgorithm::KMP:
        return kmpMatch(pattern.patterncontent, text);
    case MatchAlgorithm::BoyerMoore:
        return boyerMooreMatch(pattern.patterncontent, text);
    default:
        return false;
    }
}
