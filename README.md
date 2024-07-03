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
sudo ./main ../patterns/patternfile BF   #指定攻击算法为BF（可以改成其他）

```

增加了三种字符匹配的算法：暴力匹配，KMP，BM，在src/algorithms文件夹中
并且添加了这三种算法的测试，在test文件夹中
测试运行方法：
```
ctest -V

```

防火墙阻断文件在/src/firewall中，包含refuse（string）、show（） 和 remove（int） 函数，
它们分别用于阻断来自特定IP地址的通信、展示所有被阻断的IP地址以及移除指定编号的阻断规则。

PS:1.目前输出均为cout输出，但是重要的输出内容（所有阻断规则）构成了vector，可输出到其他地方
   2.命令需要使用sudo,因此程序需要更改程序所有者并设置setuid位，
   可用命令：
   ```
   sudo chown root:root *文件名*
   sudo chmod u+s *文件名*
   ```
