#include "pattern_reader.h"
#include "pcap_handler.h"
#include "matcher.h"
#include <iostream>
#include <vector>
#include <string>

// 定义全局变量
int minpattern_len;

// 解析算法参数
MatchAlgorithm parseAlgorithm(const std::string &algo)
{
    if (algo == "BF")
    {
        return MatchAlgorithm::BruteForce;
    }
    else if (algo == "KMP")
    {
        return MatchAlgorithm::KMP;
    }
    else if (algo == "BM")
    {
        return MatchAlgorithm::BoyerMoore;
    }
    else
    {
        throw std::invalid_argument("Unknown algorithm: " + algo);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <patternfile> <algorithm>" << std::endl;
        std::cerr << "Algorithms: BF (Brute Force), KMP (Knuth-Morris-Pratt), BM (Boyer-Moore)" << std::endl;
        return 1;
    }

    std::string patternfile = argv[1];
    std::string algo = argv[2];

    MatchAlgorithm algorithm;
    try
    {
        algorithm = parseAlgorithm(algo);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::vector<AttackPattern> patterns = readPatterns(patternfile);
    if (patterns.empty())
    {
        std::cerr << "No valid patterns found in the pattern file." << std::endl;
        return 1;
    }

    // 设置全局变量 minpattern_len
    minpattern_len = 1000;
    for (const auto &pattern : patterns)
    {
        if (pattern.patternlen < minpattern_len)
        {
            minpattern_len = pattern.patternlen;
        }
    }

    // 启动数据包捕获，传递匹配算法
    startPacketCapture(patterns, algorithm);

    return 0;
}
