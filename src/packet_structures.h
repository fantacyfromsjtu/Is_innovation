#ifndef PACKET_STRUCTURES_H
#define PACKET_STRUCTURES_H

#include <string>

// IP 头部结构
typedef struct
{
    u_char version : 4;
    u_char header_len : 4;
    u_char tos : 8;
    u_int16_t total_len : 16;
    u_int16_t ident : 16;
    u_char flags : 8;
    u_char fragment : 8;
    u_char ttl : 8;
    u_char proto : 8;
    u_int16_t checksum;
    u_char sourceIP[4];
    u_char destIP[4];
} IPHEADER;

// 数据包信息结构
typedef struct Packetinfo
{
    u_char src_ip[4];
    u_char dest_ip[4];
    std::string packetcontent;
    int contentlen;
} PACKETINFO;

#endif // PACKET_STRUCTURES_H
