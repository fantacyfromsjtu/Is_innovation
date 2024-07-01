#include "algorithms/brute_force.h"
#include "algorithms/kmp.h"
#include "algorithms/boyer_moore.h"
#include <iostream>
#include <vector>
#include <chrono>  // 用于计时
#include <cassert> // 用于验证匹配的准确性

// 用于生成随机字符串的函数
std::string generateRandomString(size_t length)
{
    const std::string characters = "abcdefghijklmnopqrstuvwxyz";
    std::string result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i)
    {
        result += characters[rand() % characters.size()];
    }
    return result;
}

// 通用测试函数
bool testAlgorithm(const std::string &pattern, const std::string &text, bool (*matchFunc)(const std::string &, const std::string &), double &matchTime)
{
    // 记录匹配开始时间
    auto start = std::chrono::high_resolution_clock::now();

    // 进行字符串匹配
    bool result = matchFunc(pattern, text);

    // 记录匹配结束时间
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    matchTime = duration.count();

    // 验证匹配的准确性
    bool expected = text.find(pattern) != std::string::npos;
    assert(result == expected && "match result does not match expected result.");

    return result == expected;
}

// 批量测试函数
void runBatchTests(size_t numPatterns, size_t minPatternLength, size_t maxPatternLength, size_t textLength, const std::string &algorithmName, bool (*matchFunc)(const std::string &, const std::string &))
{
    // 生成一个长度为 textLength 的随机字符串
    std::string text = generateRandomString(textLength);

    size_t correctMatches = 0;
    double totalMatchTime = 0.0;

    for (size_t i = 0; i < numPatterns; ++i)
    {
        size_t length = minPatternLength + rand() % (maxPatternLength - minPatternLength + 1);
        std::string pattern = generateRandomString(length);
        double matchTime = 0.0;
        if (testAlgorithm(pattern, text, matchFunc, matchTime))
        {
            correctMatches++;
        }
        totalMatchTime += matchTime;
    }

    // 计算准确率
    double accuracy = static_cast<double>(correctMatches) / numPatterns * 100.0;

    // 输出结果
    std::cout << "Algorithm: " << algorithmName << " | Total Patterns: " << numPatterns << " | Accuracy: " << accuracy << "% | Total Match Time: " << totalMatchTime << " seconds" << std::endl;
}

int main()
{
    // 设置随机数种子
    srand(time(nullptr));

    size_t numPatterns = 1000;
    size_t minPatternLength = 10;
    size_t maxPatternLength = 1000;
    size_t textLen = 1000000;

    // 运行批量测试
    std::cout << "Running Brute Force Batch Tests:" << std::endl;
    runBatchTests(numPatterns, minPatternLength, maxPatternLength, textLen, "Brute Force", bruteForceMatch);

    std::cout << "Running KMP Batch Tests:" << std::endl;
    runBatchTests(numPatterns, minPatternLength, maxPatternLength, textLen, "KMP", kmpMatch);

    std::cout << "Running Boyer-Moore Batch Tests:" << std::endl;
    runBatchTests(numPatterns, minPatternLength, maxPatternLength, textLen, "Boyer-Moore", boyerMooreMatch);

    return 0;
}
