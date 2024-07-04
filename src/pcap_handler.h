#ifndef PCAP_HANDLER_H
#define PCAP_HANDLER_H

#include <pcap.h>
#include <vector>
#include "pattern_reader.h"
#include "packet_structures.h"
#include "matcher.h"

// 自定义结构体传递参数
struct CaptureContext
{
    const std::vector<AttackPattern> &patterns;
    MatchAlgorithm algorithm;
};

// 函数声明
void startPacketCapture(const std::vector<AttackPattern> &patterns, MatchAlgorithm algorithm);
void outputAlert(const AttackPattern &pattern, const PACKETINFO &packet);

#endif // PCAP_HANDLER_H
