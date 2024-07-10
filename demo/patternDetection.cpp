#include <iostream>
#include <cstring>
#include <cstdlib>
#include <pcap.h>
#include <arpa/inet.h>
#include <string>
#include <vector>

using namespace std;

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

typedef struct Packetinfo
{
    u_char src_ip[4];
    u_char dest_ip[4];
    string packetcontent;
    int contentlen;
} PACKETINFO;

class AttackPattern
{
public:
    string attackdes;
    string patterncontent;
    int patternlen;
    AttackPattern *next;

    AttackPattern() : patternlen(0), next(nullptr) {}
};

AttackPattern *pPatternHeader = nullptr; // Global variable to store the head of the attack pattern list
int minpattern_len;                      // Minimum pattern length

int parse_para(int argc, char *argv[], string &filename)
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " : patternfile" << endl;
        return 1;
    }
    else
    {
        filename = argv[1];
        return 0;
    }
}

int readpattern(const string &patternfile)
{
    FILE *file;
    char linebuffer[256];

    file = fopen(patternfile.c_str(), "r");
    if (file == NULL)
    {
        cout << "Cannot open the pattern file! Please check it and try again!" << endl;
        return 1;
    }
    memset(linebuffer, 0, 256);
    pPatternHeader = nullptr;
    minpattern_len = 1000;

    while (fgets(linebuffer, 255, file))
    {
        AttackPattern *pOnepattern;
        int deslen;
        char *pchar;
        pchar = strchr(linebuffer, '#');
        if (pchar == NULL)
            continue;
        pOnepattern = new AttackPattern();
        deslen = pchar - linebuffer;
        pOnepattern->patternlen = strlen(linebuffer) - deslen - 2; // Adjusted for correct calculation
        pchar++;
        pOnepattern->attackdes = string(linebuffer, deslen);
        pOnepattern->patterncontent = string(pchar, pOnepattern->patternlen);
        if (pOnepattern->patternlen < minpattern_len)
            minpattern_len = pOnepattern->patternlen;
        pOnepattern->next = nullptr;

        if (pPatternHeader == nullptr)
            pPatternHeader = pOnepattern;
        else
        {
            pOnepattern->next = pPatternHeader;
            pPatternHeader = pOnepattern;
        }
        memset(linebuffer, 0, 256);
    }
    fclose(file);
    if (pPatternHeader == nullptr)
        return 1;
    return 0;
}

bool matchpattern(AttackPattern *pOnepattern, PACKETINFO *pOnepacket)
{
    //std::cout << "pattern: " << pOnepattern->patterncontent << std::endl;
    //std::cout << "text:" << pOnepacket->packetcontent << endl;
    int leftlen = pOnepacket->contentlen;
    const char *leftcontent = pOnepacket->packetcontent.c_str();
    while (leftlen >= pOnepattern->patternlen)
    {
        if (strncmp(leftcontent, pOnepattern->patterncontent.c_str(), pOnepattern->patternlen) == 0)
            return true;
        leftlen--;
        leftcontent++;
    }
    return false;
}

void output_alert(AttackPattern *pOnepattern, PACKETINFO *pOnepacket)
{
    cout << "Attack pattern detected:" << endl;
    cout << "Attack type: " << pOnepattern->attackdes << " ";
    printf("%d.%d.%d.%d ==> ", pOnepacket->src_ip[0], pOnepacket->src_ip[1], pOnepacket->src_ip[2], pOnepacket->src_ip[3]);
    printf("%d.%d.%d.%d\n", pOnepacket->dest_ip[0], pOnepacket->dest_ip[1], pOnepacket->dest_ip[2], pOnepacket->dest_ip[3]);
}

void pcap_callback(u_char *user, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
    IPHEADER *ip_header;
    PACKETINFO onepacket;
    memset(&onepacket, 0, sizeof(PACKETINFO));

    if (header->len >= 14)
        ip_header = (IPHEADER *)(pkt_data + 14);
    else
        return;

    if (ip_header->proto == 6)
    {
        onepacket.contentlen = ntohs(ip_header->total_len) - 20 - 20;
        if (onepacket.contentlen < minpattern_len)
            return;
        onepacket.packetcontent = string((char *)(pkt_data + 14 + 20 + 20), onepacket.contentlen);
        memcpy(onepacket.src_ip, ip_header->sourceIP, 4);
        memcpy(onepacket.dest_ip, ip_header->destIP, 4);
        //std::cout << "Received: " << onepacket.packetcontent << std::endl;
        AttackPattern *pOnepattern = pPatternHeader;
        while (pOnepattern != nullptr)
        {
            if (matchpattern(pOnepattern, &onepacket))
            {
                output_alert(pOnepattern, &onepacket);
            }
            pOnepattern = pOnepattern->next;
        }
    }
}

int main(int argc, char *argv[])
{
    string patternfile;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *phandle;
    bpf_u_int32 ipaddress, ipmask;
    struct bpf_program fcode;

    if (parse_para(argc, argv, patternfile))
        exit(0);
    if (readpattern(patternfile))
        exit(0);

    pcap_if_t *alldevs;
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        cerr << "Error in pcap_findalldevs: " << errbuf << endl;
        exit(1);
    }

    if (alldevs == nullptr)
    {
        cerr << "No devices found." << endl;
        exit(1);
    }

    char *device = alldevs->name;

    if (pcap_lookupnet(device, &ipaddress, &ipmask, errbuf) == -1)
        exit(0);
    else
    {
        char net[INET_ADDRSTRLEN], mask[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &ipaddress, net, sizeof(net)) == nullptr)
            exit(0);
        if (inet_ntop(AF_INET, &ipmask, mask, sizeof(mask)) == nullptr)
            exit(0);
    }

    phandle = pcap_open_live(device, 200, 1, 500, errbuf);
    if (phandle == nullptr)
        exit(0);
    if (pcap_compile(phandle, &fcode, "ip and tcp", 0, ipmask) == -1)
        exit(0);
    if (pcap_setfilter(phandle, &fcode) == -1)
        exit(0);

    cout << "Starting attack pattern detection..." << endl;
    pcap_loop(phandle, -1, pcap_callback, nullptr);

    pcap_freealldevs(alldevs);
}
