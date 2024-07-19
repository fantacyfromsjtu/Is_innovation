#include "pattern_reader.h"
#include <iostream>
#include <vector>
#include <algorithm> // 添加对算法库的引用，以便使用std::transform
#include <cctype>    // 提供tolower函数

// 转换字符串到小写
std::string toLowerCase(const std::string &input)
{
    std::string output = input;
    std::transform(output.begin(), output.end(), output.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return output;
}

// 检查模式的描述是否与内容匹配
bool checkPatterns(const std::vector<AttackPattern> &patterns)
{
    bool allCorrect = true;
    for (const auto &pattern : patterns)
    {
        // 从 patterncontent 中提取 '?' 之前的内容并转换为小写
        std::string expectedDescription = pattern.patterncontent.substr(0, pattern.patterncontent.find('?'));
        expectedDescription = toLowerCase(expectedDescription);        // 转换为小写
        std::string descriptionLower = toLowerCase(pattern.attackdes); // 描述转换为小写

        if (descriptionLower != expectedDescription)
        {
            std::cout << "Mismatch found: Description \"" << pattern.attackdes
                      << "\" does not match content prefix \"" << expectedDescription << "\"\n";
            allCorrect = false;
        }
    }
    return allCorrect;
}

int main()
{
    std::string filename = "../patterns/patternfile"; // 指定模式文件
    std::vector<AttackPattern> patterns = readPatterns(filename);

    if (patterns.empty())
    {
        std::cerr << "No patterns were read from the file.\n";
        return 1;
    }

    // 检查读取的模式是否全部正确
    if (checkPatterns(patterns))
    {
        std::cout << "All patterns correctly formatted and test passed.\n";
    }
    else
    {
        std::cout << "Some patterns were incorrectly formatted. Test failed.\n";
    }

    return 0;
}
