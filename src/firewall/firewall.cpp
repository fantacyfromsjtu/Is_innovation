/*本文件定义了3个函数，包含refuse（string）、show（） 和 remove（int） 函数，
它们分别用于阻断来自特定IP地址的通信、展示所有被阻断的IP地址以及移除指定编号的阻断规则。

PS:1.目前输出均为cout输出，但是重要的输出内容（所有阻断规则）构成了vector，可输出到其他地方
   2.命令需要使用sudo,因此程序需要更改程序所有者并设置setuid位，
   可用命令：
   sudo chown root:root *文件名*
   sudo chmod u+s *文件名*

*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>

//阻断ip，调用后提示输入ip地址，阻断来自此ip地址的通信
void refuse(const std::string &ip) {
    std::string command = "sudo iptables -A INPUT -s " + ip + " -j DROP";//命令合成
    int result = system(command.c_str());//调用system（）函数执行命令行命令
    if (result == 0) {
        std::cout << "IP " << ip << " has been blocked." << std::endl;//成功提示
    } else {
        std::cerr << "Failed to block IP " << ip << std::endl;//失败提示
    }
}

//展示目前所有的阻断规则
void show() {
    FILE *fp;
    char buffer[128];
    std::vector<std::string> rules;
    fp = popen("sudo iptables -L INPUT -n --line-numbers", "r");//使用popen命令，将命令输出作为文件流
    if (fp == nullptr) {
        std::cerr << "Failed to run iptables command." << std::endl;
        return;
    }//失败提示

    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        rules.push_back(buffer);
    }//将文件流读入容器，方便处理和输出

    std::cout << "Current iptables INPUT rules:" << std::endl;
    for (const auto &rule : rules) {
        std::cout << rule;
    }//使用C++11新引入的规则，方便容器遍历和输出
}

//移除序号对应的阻断规则
void remove(int rule_number) {
    std::ostringstream command;//定义输出字符串流
    command << "sudo iptables -D INPUT " << rule_number;//合成命令
    int result = system(command.str().c_str());//执行命令
    if (result == 0) {
        std::cout << "Rule number " << rule_number << " has been removed." << std::endl;
    } else {
        std::cerr << "Failed to remove rule number " << rule_number << std::endl;
    }
}

//测试代码，确认上方所有代码均可用，可删去
// int main() {
//     int choice;
//     std::string ip;
//     int rule_number;

//     while (true) {
//         std::cout << "\n1. Block an IP\n2. Show blocked IPs\n3. Remove a block rule\n4. Exit\n";
//         std::cout << "Enter your choice: ";
//         std::cin >> choice;

//         switch (choice) {
//             case 1:
//                 std::cout << "Enter the IP address to block: ";
//                 std::cin >> ip;
//                 refuse(ip);
//                 break;
//             case 2:
//                 show();
//                 break;
//             case 3:
//                 std::cout << "Enter the rule number to remove: ";
//                 std::cin >> rule_number;
//                 remove(rule_number);
//                 break;
//             case 4:
//                 return 0;
//             default:
//                 std::cerr << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
//                 break;
//         }
//     }

//     return 0;
// }
