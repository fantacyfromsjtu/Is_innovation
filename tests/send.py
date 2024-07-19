from scapy.all import IP, TCP, send, RandShort
import time

# 目标IP和端口（假设本机测试，端口为你抓包模块监听的端口）
target_ip = "127.0.0.1"
target_port = 80

# 定义发送的数据包类型
def send_packets():
    packet_count = 5  # 发送的数据包数量
    for _ in range(packet_count):
        # 创建具有随机源端口的TCP数据包
        source_port = RandShort()
        packet = IP(dst=target_ip) / TCP(sport=source_port, dport=target_port, flags='S')
        
        # 发送数据包
        send(packet)
        
        # 打印发送信息
        print(f"Sent TCP SYN packet from port {source_port} to {target_ip}:{target_port}")
        
        # 等待一秒钟，以便你的抓包模块有时间处理包
        time.sleep(1)

if __name__ == "__main__":
    send_packets()
