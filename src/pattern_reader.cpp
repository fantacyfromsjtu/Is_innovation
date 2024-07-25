#include "pattern_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// 读取攻击模式文件的实现
std::vector<AttackPattern> readPatterns(const std::string &filename)
{
    std::vector<AttackPattern> patterns; // 存储读取的攻击模式
    std::ifstream file(filename);        // 打开文件流
    if (!file.is_open())                 // 检查文件是否成功打开
    {
        std::cerr << "Cannot open the pattern file! Please check it and try again!" << std::endl; // 输出错误信息
        return patterns;                                                                          // 返回空模式列表
    }

    std::string line;
    while (std::getline(file, line)) // 逐行读取文件内容
    {
        std::istringstream iss(line); // 使用字符串流处理每行内容
        std::string attackdes, patterncontent;
        if (std::getline(iss, attackdes, '#') && std::getline(iss, patterncontent)) // 使用#符号分隔攻击描述和模式内容
        {
            AttackPattern pattern;                      // 创建攻击模式结构体
            pattern.attackdes = attackdes;              // 设置攻击描述
            pattern.patterncontent = patterncontent;    // 设置模式内容
            pattern.patternlen = patterncontent.size(); // 计算模式长度
            patterns.push_back(pattern);                // 将模式添加到列表中
        }
    }
    file.close();    // 关闭文件流
    return patterns; // 返回读取的攻击模式列表
}
