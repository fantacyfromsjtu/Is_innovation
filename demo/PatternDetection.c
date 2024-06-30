#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

typedef struct { //ip头格式
	u_char version:4;
	u_char header_len:4;
	u_char tos:8;
	u_int16_t total_len:16;
	u_int16_t ident:16;
	u_char flags:8;
	u_char fragment:8;
	u_char ttl:8;
	u_char proto:8;
	u_int16_t checksum;
	u_char sourceIP[4];
	u_char destIP[4];
}IPHEADER;

typedef struct Packetinfo{
	u_char src_ip[4];
	u_char dest_ip[4];
	char *packetcontent;
	int contentlen;
}PACKETINFO;

typedef struct AttackPattern{
	char attackdes[256];
	char patterncontent[256];
	int patternlen;
	struct AttackPattern *next;
}ATTACKPATTERN;

ATTACKPATTERN* pPatternHeader;//全局变量，保存攻击模式链表头
int minpattern_len;    //最短模式的长度

int parse_para(int argc,char*argv[],char *filename){
	if(argc != 2) {
		printf("Usage %s : patternfile \n",argv[0]);
		return 1;
	}else{
		bzero(filename, 256);
		strncpy(filename,argv[1],255);
  		return 0;
	}
}

int readpattern(char *patternfile){
	FILE *file;
	char linebuffer[256];

	file = fopen(patternfile,"r");
	if ( file == NULL) {
		printf("Cann't open the pattern file! Please check it and try again! \n");
		return 1;
	}
	bzero(linebuffer,256);
	pPatternHeader = NULL;
	minpattern_len = 1000;

	while(fgets(linebuffer,255,file)){
		ATTACKPATTERN *pOnepattern;
		int deslen;
		char *pchar;
		pchar = strchr(linebuffer,'#');
		if (pchar == NULL)
			continue;
		pOnepattern = malloc(sizeof(ATTACKPATTERN));
		deslen = pchar - linebuffer;
		pOnepattern->patternlen = strlen(linebuffer) - deslen -1 -1 ;
		pchar ++;
		memcpy(pOnepattern->attackdes, linebuffer, deslen);
		memcpy(pOnepattern->patterncontent, pchar, pOnepattern->patternlen);
		if (pOnepattern->patternlen < minpattern_len)
			minpattern_len = pOnepattern->patternlen;
		pOnepattern->next = NULL;

		if (pPatternHeader == NULL)
			pPatternHeader = pOnepattern;
		else{
			pOnepattern->next = pPatternHeader;
			pPatternHeader = pOnepattern;
		}
		bzero(linebuffer,256);
	}
	if (pPatternHeader == NULL) 
		return 1;
	return 0;
}

int matchpattern(ATTACKPATTERN *pOnepattern, PACKETINFO *pOnepacket){
	int leftlen;
	char *leftcontent;
	leftlen = pOnepacket-> contentlen;
	leftcontent = pOnepacket -> packetcontent;
	while(leftlen >= pOnepattern->patternlen){
		if (strncmp(leftcontent,pOnepattern->patterncontent,pOnepattern->patternlen) == 0)
			return 1;
		leftlen --;
		leftcontent ++;
	}
	return 0;
}

void output_alert(ATTACKPATTERN *pOnepattern,PACKETINFO *pOnepacket)
{
  	printf("发现特征串攻击:\n     攻击类型  %s   ", pOnepattern->attackdes);
  	printf("%d.%d.%d.%d ==> ",pOnepacket->src_ip[0],pOnepacket->src_ip[1],pOnepacket->src_ip[2],pOnepacket->src_ip[3]);
  	printf("%d.%d.%d.%d\n",pOnepacket->dest_ip[0],pOnepacket->dest_ip[1],pOnepacket->dest_ip[2],pOnepacket->dest_ip[3]);
}




void pcap_callback(u_char *user,const struct pcap_pkthdr *header,const u_char *pkt_data)
{
  	IPHEADER *ip_header;
	PACKETINFO onepacket;
	ATTACKPATTERN *pOnepattern;
  	bzero(&onepacket,sizeof(PACKETINFO));

  	if(header->len >= 14)
    	ip_header=(IPHEADER*)(pkt_data+14);
	else 
		return;
  	if(ip_header->proto == 6){
		onepacket.contentlen = ip_header->total_len - 20 - 20;
		if (onepacket.contentlen < minpattern_len)
			return;
		onepacket.packetcontent = (char *)(pkt_data + 14 + 20 + 20);
   	strncpy(onepacket.src_ip,ip_header->sourceIP,4);
    	strncpy(onepacket.dest_ip,ip_header->destIP,4);

    	ATTACKPATTERN *pOnepattern = pPatternHeader;
		while(pOnepattern != NULL){
			if (matchpattern(pOnepattern, &onepacket)){
				output_alert(pOnepattern, &onepacket);
			}
			pOnepattern = pOnepattern->next;
    		}
	}
}

int main(int argc,char *argv[])
{ 
   char patternfile[256];  //保存攻击模式文件名
  	char *device;
  	char errbuf[PCAP_ERRBUF_SIZE];
  	pcap_t *phandle;
  	bpf_u_int32 ipaddress, ipmask;
  	struct bpf_program fcode;
	if(parse_para(argc,argv,patternfile))  //解析参数
		exit(0);
	if (readpattern(patternfile))
		exit(0);

  	if((device = pcap_lookupdev(errbuf)) == NULL) exit(0);                 //获得可用的网络设备名.
  	if(pcap_lookupnet(device,&ipaddress,&ipmask,errbuf)==-1)    //获得ip和子网掩码
   	exit(0);
  	else {
    	char net[INET_ADDRSTRLEN],mask[INET_ADDRSTRLEN];
    	if(inet_ntop(AF_INET,&ipaddress,net,sizeof(net)) == NULL) 
			exit(0);
      else 
			if(inet_ntop(AF_INET,&ipmask,mask,sizeof(mask)) == NULL)	exit(0);
    	}
  	phandle = pcap_open_live(device,200,1,500,errbuf);                    //打开设备
  	if(phandle == NULL)
	  	exit(0);
  	if(pcap_compile(phandle,&fcode,"ip and tcp",0,ipmask) == -1) exit(0);         //设置过滤器，只捕获ip&tcp报头的包
  	if(pcap_setfilter(phandle,&fcode) == -1)
	 	exit(0);
 	printf("开始特征串攻击检测.....\n");  //此函数设置过滤器并开始进行数据包的捕捉
  	pcap_loop(phandle,-1,pcap_callback	,NULL);     
}
