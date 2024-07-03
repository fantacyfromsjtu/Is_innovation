#ifndef PATTERN_READER_H
#define PATTERN_READER_H

#include <string>
#include <vector>
#include "packet_structures.h" // 引用packet_structures.h以获取AttackPattern定义

std::vector<AttackPattern> readPatterns(const std::string &filename);

#endif // PATTERN_READER_H
