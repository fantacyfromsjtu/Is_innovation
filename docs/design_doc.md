# 设计文档
## 目录结构
```
IDS/
├── src/
│   ├── main.cpp                  # 主程序
│   ├── pattern_reader.cpp        # 攻击模式读取模块
│   ├── pattern_reader.h          # 攻击模式读取模块头文件
│   ├── pcap_handler.cpp          # 数据包捕获和处理模块
│   ├── pcap_handler.h            # 数据包捕获和处理模块头文件
│   ├── matcher.cpp               # 匹配算法调度模块
│   ├── matcher.h                 # 匹配算法调度模块头文件
│   ├── algorithms/               # 匹配算法文件夹
│       ├── brute_force.cpp       # Brute Force算法实现
│       ├── brute_force.h         # Brute Force算法头文件
│       ├── kmp.cpp               # KMP算法实现
│       ├── kmp.h                 # KMP算法头文件
│       ├── boyer_moore.cpp       # Boyer-Moore算法实现
│       ├── boyer_moore.h         # Boyer-Moore算法头文件
├── patterns/
│   └── patternfile               # 攻击模式定义文件
├── docs/
│   ├── design_doc.md             # 设计文档
│   ├── user_guide.md             # 用户指南
├── build/                        # 编译输出目录
├── tests/                        # 测试代码
│   ├── test_pattern_reader.cpp
│   ├── test_pcap_handler.cpp
│   ├── test_matcher.cpp
│   ├── test_brute_force.cpp
│   ├── test_kmp.cpp
│   ├── test_boyer_moore.cpp
├── CMakeLists.txt                # CMake构建文件
└── README.md                     # 项目简介

```
