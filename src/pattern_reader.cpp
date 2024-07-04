#include "pattern_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// 读取攻击模式文件的实现
std::vector<AttackPattern> readPatterns(const std::string &filename)
{
    std::vector<AttackPattern> patterns;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Cannot open the pattern file! Please check it and try again!" << std::endl;
        return patterns;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string attackdes, patterncontent;
        if (std::getline(iss, attackdes, '#') && std::getline(iss, patterncontent))
        {
            AttackPattern pattern;
            pattern.attackdes = attackdes;
            pattern.patterncontent = patterncontent;
            pattern.patternlen = patterncontent.size();
            patterns.push_back(pattern);
        }
    }
    file.close();
    return patterns;
}
