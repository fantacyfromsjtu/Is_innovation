#ifndef PACKET_STRUCTURES_H
#define PACKET_STRUCTURES_H

#include <string>

// IP 头部结构
typedef struct
{
    u_char version : 4;       // IP版本号
    u_char header_len : 4;    // 头部长度
    u_char tos : 8;           // 服务类型
    u_int16_t total_len : 16; // 总长度
    u_int16_t ident : 16;     // 标识
    u_char flags : 8;         // 标志位
    u_char fragment : 8;      // 分段偏移
    u_char ttl : 8;           // 存活时间
    u_char proto : 8;         // 协议
    u_int16_t checksum;       // 校验和
    u_char sourceIP[4];       // 源IP地址
    u_char destIP[4];         // 目的IP地址
} IPHEADER;

// 数据包信息结构
typedef struct Packetinfo
{
    u_char src_ip[4];          // 源IP地址
    u_char dest_ip[4];         // 目的IP地址
    std::string packetcontent; // 数据包内容
    int contentlen;            // 内容长度
} PACKETINFO;

#endif // PACKET_STRUCTURES_H
