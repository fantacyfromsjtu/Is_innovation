/*
攻击模式读取模块
*/
#include "pattern_reader.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<AttackPattern> readPatterns(const std::string &patternfile)
{
    std::vector<AttackPattern> patterns;
    std::ifstream file(patternfile);
    if (!file.is_open())
    {
        std::cerr << "Cannot open the pattern file! Please check it and try again!" << std::endl;
        return patterns;
    }

    std::string line;
    while (std::getline(file, line))
    {
        size_t pos = line.find('#');
        if (pos != std::string::npos)
        {
            AttackPattern pattern;
            pattern.attackdes = line.substr(0, pos);
            pattern.patterncontent = line.substr(pos + 1);
            pattern.patternlen = pattern.patterncontent.size();
            patterns.push_back(pattern);
        }
    }

    return patterns;
}
