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
```

项目运行方法：
```
cd ~/IDS/build
rm -rf *
cmake ..
make
sudo ./main ../patterns/patternfile BF   #指定攻击算法为BF（因为其他还没写

```

增加了三种字符匹配的算法：暴力匹配，KMP，BM，在src/algorithms文件夹中
并且添加了这三种算法的测试，在test文件夹中
测试运行方法：
```
ctest -V

```