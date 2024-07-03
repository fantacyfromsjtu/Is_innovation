/*
特征串匹配算法模块
*/
#include "matcher.h"
#include <cstring>
#include "algorithms/brute_force.h"
#include "algorithms/kmp.h"
#include "algorithms/boyer_moore.h"
#include "algorithms/aho_corasick.h"



bool bruteForceMatch(const char *pattern, const char *text)
{
    std::string pat(pattern);
    std::string txt(text);
    return bruteForceMatch(pat, txt);
}

bool kmpMatch(const char *pattern, const char *text)
{
    std::string pat(pattern);
    std::string txt(text);
    return kmpMatch(pat, txt);
}

bool boyerMooreMatch(const char *pattern, const char *text)
{
    std::string pat(pattern);
    std::string txt(text);
    return boyerMooreMatch(pat, txt);
}

std::vector<std::pair<int, int>> ahoCorasickMatch(const std::vector<std::string> &patterns, const std::string &text)
{
    AhoCorasick ac(patterns);
    return ac.search(text);
}
