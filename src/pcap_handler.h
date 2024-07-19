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

struct CaptureContext
{
    const std::vector<AttackPattern> *patterns;
    MatchAlgorithm algorithm;
};
// 定义回调函数的类型
typedef std::function<void(const PACKETINFO &)> PacketCallback;
void setPacketCallback(const PacketCallback &callback);
void pcapCallback(u_char *user, const struct pcap_pkthdr *header, const u_char *pkt_data);
void startPacketCapture(const std::vector<AttackPattern> &patterns, MatchAlgorithm algorithm);
void packetProcessor(CaptureContext context);
void outputAlert(const AttackPattern &pattern, const PACKETINFO &packet);

#endif // PCAP_HANDLER_H
