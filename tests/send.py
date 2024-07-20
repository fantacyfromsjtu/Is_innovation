import requests
import time
import random
import logging
import os

normal_requests = [
    "http://example.com/?search=hello",
    "http://example.com/?search=test",
    "http://example.com/?page=home",
    "http://example.com/?page=about",
    "http://example.com/?id=1234",
    "http://example.com/?query=example"
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

    num_requests = 100
    print(str(num_requests) +" requests will be sent.")
    total_requests = 0
    total_response_time = 0
    attack_detected = 0

    for _ in range(num_requests):
        url = random.choice(normal_requests)

        status_code, response_time = send_request(url)
        if status_code and response_time is not None:
                total_requests += 1
                total_response_time += response_time

            # 等待一段时间再发送下一个请求，避免服务器过载
        time.sleep(random.uniform(1.0, 1.0))

    average_response_time = total_response_time / total_requests if total_requests else 0
    detection_rate = attack_detected / num_requests if num_requests else 0

    logging.info(f"Total Requests: {total_requests}")
    logging.info(f"Average Response Time: {average_response_time:.4f} seconds")


if __name__ == "__main__":
    main()
