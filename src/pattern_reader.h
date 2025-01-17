#ifndef PATTERN_READER_H
#define PATTERN_READER_H

#include <string>
#include <vector>

// 攻击模式结构体
struct AttackPattern
{
    std::string attackdes;      // 攻击描述
    std::string patterncontent; // 模式内容
    int patternlen;             // 模式长度
};

// 读取攻击模式文件
std::vector<AttackPattern> readPatterns(const std::string &filename);

#endif // PATTERN_READER_H
