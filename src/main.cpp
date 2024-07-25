// main.cpp
// 主程序入口，用于启动 IDS 系统的数据包捕获和分析。
// 包含模式读取、数据包处理、匹配算法和防火墙等头文件。
// 全局变量 minpattern_len 被其他文件引用，实际定义未在此文件中。

#include "pattern_reader.h"
#include "pcap_handler.h"
#include "matcher.h"
#include "firewall.h"
#include <iostream>
#include <vector>
#include <string>

// 定义全局变量，外部声明
extern int minpattern_len;

// 解析算法参数，将算法名称转换为枚举类型
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

// 主函数，程序入口
int main(int argc, char *argv[])
{
    // 检查命令行参数是否足够
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <patternfile> <algorithm>" << std::endl;
        std::cerr << "Algorithms: BF (Brute Force), KMP (Knuth-Morris-Pratt), BM (Boyer-Moore)" << std::endl;
        return 1; // 参数不足，返回错误码 1
    }

    // 获取命令行参数，模式文件名和算法名称
    std::string patternfile = argv[1];
    std::string algo = argv[2];

    MatchAlgorithm algorithm;
    try
    {
        // 解析算法名称为枚举类型
        algorithm = parseAlgorithm(algo);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl; // 捕获并打印异常信息
        return 1;                           // 算法名称无效，返回错误码 1
    }

    // 从模式文件中读取攻击模式列表
    std::vector<AttackPattern> patterns = readPatterns(patternfile);
    if (patterns.empty())
    {
        std::cerr << "No valid patterns found in the pattern file." << std::endl;
        return 1; // 模式文件中没有有效模式，返回错误码 1
    }

    // 设置全局变量 minpattern_len 为模式中最小的长度
    minpattern_len = 1000; // 初始化为较大的值，以便找到最小值
    for (const auto &pattern : patterns)
    {
        if (pattern.patternlen < minpattern_len)
        {
            minpattern_len = pattern.patternlen; // 更新最小长度
        }
    }

    // 启动数据包捕获，传递模式列表和匹配算法
    startPacketCapture(patterns, algorithm);

    return 0; // 程序正常退出
}
