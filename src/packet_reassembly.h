#ifndef PACKET_REASSEMBLY_H
#define PACKET_REASSEMBLY_H

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include "packet_structures.h"

class PacketReassembler
{
public:
    void addPacket(const PACKETINFO &packet);
    std::string getReassembledData(const u_char src_ip[4], const u_char dest_ip[4]);

private:
    std::map<std::pair<std::array<u_char, 4>, std::array<u_char, 4>>, std::vector<std::string>> packetFragments;
};

#endif // PACKET_REASSEMBLY_H
