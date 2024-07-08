#include "pcap_handler.h"
#include "matcher.h"
#include <iostream>
#include <cstring>
#include <pcap.h>
#include <arpa/inet.h>

// 使用 extern 声明全局变量
extern int minpattern_len;

// pcap回调函数，用于处理捕获的数据包
void pcapCallback(u_char *user, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
    auto context = reinterpret_cast<CaptureContext *>(user);
    const std::vector<AttackPattern> &patterns = *context->patterns; // 解引用指针获取模式向量
    const auto algorithm = context->algorithm;

    if (header->len < 14)
        return;

    // 解析 IP 头部
    const IPHEADER *ip_header = reinterpret_cast<const IPHEADER *>(pkt_data + 14);
    if (ip_header->proto != 6)
        return; // 只处理 TCP 数据包

    // 解析 TCP 头部并获取数据包内容
    int ip_header_length = ip_header->header_len * 4;
    const u_char *tcp_header = pkt_data + 14 + ip_header_length;
    int tcp_header_length = ((*tcp_header) >> 4) * 4;
    const u_char *payload = tcp_header + tcp_header_length;
    int payload_length = ntohs(ip_header->total_len) - (ip_header_length + tcp_header_length);

    if (payload_length < 0 || payload_length > 1500) // 合理性检查
    {
        return;
    }

    // 构建数据包信息
    PACKETINFO onepacket;
    memcpy(onepacket.src_ip, ip_header->sourceIP, 4);
    memcpy(onepacket.dest_ip, ip_header->destIP, 4);
    onepacket.packetcontent = std::string(reinterpret_cast<const char *>(payload), payload_length);
    onepacket.contentlen = payload_length;

    // 打印接收到的数据包片段
    std::cout << "Received packet fragment: " << onepacket.packetcontent << std::endl;

    // 只检测单个报文
    for (const auto &pattern : patterns)
    {
        if (matchPattern(pattern, onepacket.packetcontent, algorithm))
        {
            std::cout << "Match found in single packet: " << onepacket.packetcontent << std::endl;
            outputAlert(pattern, onepacket);
        }
    }
}

// 启动数据包捕获
void startPacketCapture(const std::vector<AttackPattern> &patterns, MatchAlgorithm algorithm)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    pcap_if_t *alldevs;

    // 获取网络设备列表
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
        return;
    }

    if (alldevs == nullptr)
    {
        std::cerr << "No devices found." << std::endl;
        return;
    }

    char *device = alldevs->name;

    // 获取网络设备的网络地址和掩码
    bpf_u_int32 ipaddress, ipmask;
    if (pcap_lookupnet(device, &ipaddress, &ipmask, errbuf) == -1)
    {
        std::cerr << "Can't get netmask for device " << device << std::endl;
        return;
    }

    // 打开网络设备进行捕获
    handle = pcap_open_live(device, 1500, 1, 1000, errbuf); // 设置捕获大小为1500字节
    if (handle == nullptr)
    {
        std::cerr << "Couldn't open device " << device << ": " << errbuf << std::endl;
        return;
    }

    // 设置过滤器，只捕获 80 端口的 IP 和 TCP 数据包
    struct bpf_program filter;
    if (pcap_compile(handle, &filter, "ip and tcp and port 80", 0, ipmask) == -1)
    {
        std::cerr << "Couldn't parse filter: ip and tcp and port 80" << std::endl;
        return;
    }

    if (pcap_setfilter(handle, &filter) == -1)
    {
        std::cerr << "Couldn't install filter: ip and tcp and port 80" << std::endl;
        return;
    }

    std::cout << "Starting attack pattern detection..." << std::endl;
    CaptureContext context = {&patterns, algorithm};
    pcap_loop(handle, 0, pcapCallback, reinterpret_cast<u_char *>(&context));

    pcap_freealldevs(alldevs);
}

// 输出警报信息
void outputAlert(const AttackPattern &pattern, const PACKETINFO &packet)
{
    std::cout << "Attack pattern detected:" << std::endl;
    std::cout << "Attack type: " << pattern.attackdes << " ";
    printf("%d.%d.%d.%d ==> ", packet.src_ip[0], packet.src_ip[1], packet.src_ip[2], packet.src_ip[3]);
    printf("%d.%d.%d.%d\n", packet.dest_ip[0], packet.dest_ip[1], packet.dest_ip[2], packet.dest_ip[3]);
}
