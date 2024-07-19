#include <cassert>
#include <iostream>
#include "pcap_handler.h"

// 全局变量来存储接收到的数据内容
std::string receivedData;

// 测试用的回调函数
void testCallback(const PACKETINFO &packet)
{
    std::cout << "Received packet: " << packet.packetcontent << std::endl;
    receivedData = packet.packetcontent;
}

int main()
{
    // 设置回调
    setPacketCallback(testCallback); // 假设 pcap_handler.h 提供了设置回调函数的接口

    // 运行抓包模块
    std::vector<AttackPattern> patterns;              // 假设已正确设置
    MatchAlgorithm algo = MatchAlgorithm::BruteForce; // 使用暴力匹配算法作为示例
    startPacketCapture(patterns, algo);

    // 等待或睡眠一段时间，确保数据包被处理
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 进行断言验证，确保接收到的内容是期望的内容
    assert(receivedData.find("expected content") != std::string::npos);

    return 0;
}
