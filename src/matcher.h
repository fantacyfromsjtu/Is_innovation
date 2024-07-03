#ifndef MATCHER_H
#define MATCHER_H

#include <vector>
#include <string>

enum class MatchAlgorithm
{
    BruteForce,
    KMP,
    BoyerMoore,
    AhoCorasick
};

extern int minpattern_len;

bool bruteForceMatch(const std::string &pattern, const std::string &text);
bool kmpMatch(const std::string &pattern, const std::string &text);
bool boyerMooreMatch(const std::string &pattern, const std::string &text);
std::vector<std::pair<int, int>> ahoCorasickMatch(const std::vector<std::string> &patterns, const std::string &text);

#endif // MATCHER_H
