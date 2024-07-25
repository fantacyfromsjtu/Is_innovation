# 设计文档
## 目录结构
```
IDS/
├── src/
│   ├── main.cpp
│   ├── pattern_reader.cpp
│   ├── pattern_reader.h
│   ├── pcap_handler.cpp
│   ├── pcap_handler.h
│   ├── matcher.cpp
│   ├── matcher.h
│   ├── packet_reassembly.cpp
│   ├── packet_reassembly.h
│   ├── firewall.cpp
│   ├── firewall.h
│   ├── packet_structures.h
│   ├── algorithms/
│       ├── brute_force.cpp
│       ├── brute_force.h
│       ├── kmp.cpp
│       ├── kmp.h
│       ├── boyer_moore.cpp
│       ├── boyer_moore.h
├── gui/
│   ├── main_window.c
│   ├── main_window.glade
├── tests/
│   ├── test_algorithms.cpp
│   ├── test_matcher.cpp
│   ├── test_pattern_reader.cpp
│   ├── test_pcap_handler.cpp
│   ├── attack.py
│   ├── send.py
├── database/
│   ├── load.cpp
│   ├── read_db.cpp
│   ├── patternfile2sql.py
├── patterns/
│   └── patternfile
├── CMakeLists.txt


```


### 目录结构详解

**`IDS/`**：这是项目的根目录，其中包含所有源代码、文档、模式文件、测试和构建配置。

#### `src/`：源代码目录

- **`main.cpp`**：主程序文件，负责初始化程序、配置解析、调用数据包处理模块和启动入侵检测流程。
- **`pattern_reader.cpp` 和 `pattern_reader.h`**：这两个文件定义了攻击模式读取模块，负责从文件中读取和解析攻击模式，提供接口给其他模块查询和获取这些模式。
- **`pcap_handler.cpp` 和 `pcap_handler.h`**：数据包捕获和处理模块，使用libpcap库捕获网络流量，解析数据包内容，并将数据包传递给匹配模块。
- **`matcher.cpp` 和 `matcher.h`**：匹配算法调度模块，负责选择和调用不同的字符串匹配算法来检测攻击模式是否出现在网络流量中。
- 
- **`algorithms/`**：包含所有字符串匹配算法的实现。
  - **`brute_force.cpp` 和 `brute_force.h`**：暴力匹配算法的实现。
  - **`kmp.cpp` 和 `kmp.h`**：KMP (Knuth-Morris-Pratt) 算法的实现，用于更高效的字符串匹配。
  - **`boyer_moore.cpp` 和 `boyer_moore.h`**：Boyer-Moore 算法的实现，这是一种效率非常高的字符串搜索算法。

#### `gui/`：图形界面代码目录
- **`main_window.c`**：主窗口程序，包含GTK+主窗口的创建和初始化代码，负责管理图形界面事件和交互。
- **`main_window.glade`**：Glade UI文件，定义图形界面的布局和控件，通过Glade工具生成，用于简化GTK+ UI的设计和维护。
- **`main_window`**：图形化可执行程序。

#### `patterns/`

- **`patternfile`**：包含定义好的攻击模式。这些模式用于检测可能的入侵或恶意活动。

#### `docs/`

- **`design_doc.md`**：本文件，详细描述了项目设计。

#### `build/`

- 这个目录用于存放编译后的可执行文件和其他构建产物。它通常不包含在源代码库中，而是在构建过程中创建。

#### `tests/`

- **`test_pattern_reader.cpp`**：针对模式读取模块的单元测试。
- **`test_pcap_handler.cpp`**：针对数据包处理模块的单元测试。
- **`test_matcher.cpp`**：针对匹配调度模块的单元测试。
- **`test_algorithms.cpp`**：针对包含在`algorithms/`目录下的各种字符串匹配算法的单元测试。

#### `CMakeLists.txt`

- **`CMakeLists.txt`**：CMake构建配置文件，定义了如何构建项目，包括编译选项、源文件列表和外部依赖。
