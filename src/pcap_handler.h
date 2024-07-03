#ifndef PCAP_HANDLER_H
#define PCAP_HANDLER_H

#include <pcap.h>
#include <vector>
#include "packet_structures.h" // 引用 packet_structures.h 以获取 AttackPattern 和 CaptureContext 定义

// 声明全局变量
extern int minpattern_len;

// 函数声明
void startPacketCapture(const std::vector<AttackPattern> &patterns, MatchAlgorithm algorithm);
void outputAlert(const AttackPattern &pattern, const PACKETINFO &packet);

#endif // PCAP_HANDLER_H
