#include "packet_reassembly.h"
#include <cstring>
#include <array>

void PacketReassembler::addPacket(const PACKETINFO &packet)
{
    std::array<u_char, 4> src_ip;
    std::array<u_char, 4> dest_ip;
    std::memcpy(src_ip.data(), packet.src_ip, 4);
    std::memcpy(dest_ip.data(), packet.dest_ip, 4);

    auto key = std::make_pair(src_ip, dest_ip);
    packetFragments[key].push_back(packet.packetcontent);
}

std::string PacketReassembler::getReassembledData(const u_char src_ip[4], const u_char dest_ip[4])
{
    std::array<u_char, 4> src_ip_arr;
    std::array<u_char, 4> dest_ip_arr;
    std::memcpy(src_ip_arr.data(), src_ip, 4);
    std::memcpy(dest_ip_arr.data(), dest_ip, 4);

    auto key = std::make_pair(src_ip_arr, dest_ip_arr);
    std::string reassembledData;

    if (packetFragments.find(key) != packetFragments.end())
    {
        for (const auto &fragment : packetFragments[key])
        {
            reassembledData += fragment;
        }
        packetFragments.erase(key);
    }

    return reassembledData;
}
