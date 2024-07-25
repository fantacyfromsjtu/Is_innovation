#ifndef PCAP_HANDLER_H
#define PCAP_HANDLER_H

#include "packet_structures.h"
#include "matcher.h"
#include <vector>
#include <functional>
#include <pcap.h>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

// 数据包捕获的上下文信息结构体
struct CaptureContext
{
    const std::vector<AttackPattern> *patterns; // 指向要匹配的攻击模式的指针
    MatchAlgorithm algorithm;                   // 使用的匹配算法
};

// 数据包回调函数类型定义
typedef std::function<void(const PACKETINFO &)> PacketCallback;

// 函数声明
void setPacketCallback(const PacketCallback &callback);                                        // 设置数据包处理的回调函数
void pcapCallback(u_char *user, const struct pcap_pkthdr *header, const u_char *pkt_data);     // libpcap 的回调函数
void startPacketCapture(const std::vector<AttackPattern> &patterns, MatchAlgorithm algorithm); // 开始数据包捕获
void packetProcessor(CaptureContext context);                                                  // 根据上下文处理捕获的数据包
void outputAlert(const AttackPattern &pattern, const PACKETINFO &packet);                      // 匹配攻击模式时输出警报

#endif // PCAP_HANDLER_H
