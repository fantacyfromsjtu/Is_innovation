/*
数据包捕获和处理模块头文件
*/
#ifndef PCAP_HANDLER_H
#define PCAP_HANDLER_H

#include <pcap.h>
#include <vector>
#include "pattern_reader.h"
#include "matcher.h"
#include "packet_structures.h"

// 声明全局变量
extern int minpattern_len;

// 自定义结构体传递参数
struct CaptureContext
{
    const std::vector<AttackPattern> *patterns;
    MatchAlgorithm algorithm;
};

// 函数声明
void startPacketCapture(const std::vector<AttackPattern> &patterns, MatchAlgorithm algorithm);
void outputAlert(const AttackPattern &pattern, const PACKETINFO &packet);

#endif // PCAP_HANDLER_H
