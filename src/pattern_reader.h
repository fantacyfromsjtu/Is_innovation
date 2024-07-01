/*
攻击模式读取模块头文件
*/
#pragma once
#include <string>
#include <vector>

class AttackPattern
{
public:
    std::string attackdes;
    std::string patterncontent;
    int patternlen;
    AttackPattern *next;

    AttackPattern() : patternlen(0), next(nullptr) {}
};

std::vector<AttackPattern> readPatterns(const std::string &patternfile);
