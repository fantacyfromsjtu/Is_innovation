#ifndef FIREWALL_H
#define FIREWALL_H

#include <string>

// 阻断指定 IP 地址的流量
void refuse(const std::string &ip);

// 展示目前所有的阻断规则
void show();

// 移除指定序号的阻断规则
void remove(int rule_number);

#endif // FIREWALL_H
