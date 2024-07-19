cmake_minimum_required(VERSION 3.10)
project(IDS)

set(CMAKE_CXX_STANDARD 14)

# 添加源文件
set(SOURCES
    src/main.cpp
    src/pattern_reader.cpp
    src/pcap_handler.cpp
    src/matcher.cpp
    src/algorithms/brute_force.cpp
    src/algorithms/kmp.cpp
    src/algorithms/boyer_moore.cpp
    src/packet_reassembly.cpp
)

# 添加头文件目录
include_directories(src)
include_directories(src/algorithms)

# 生成可执行文件
add_executable(main ${SOURCES})

# 链接 libpcap 库
target_link_libraries(main pcap)

# 启用测试
enable_testing()

# 添加综合测试文件
add_executable(test_algorithms tests/test_algorithms.cpp src/algorithms/brute_force.cpp src/algorithms/kmp.cpp src/algorithms/boyer_moore.cpp)
add_executable(test_pattern_reader tests/test_pattern_reader.cpp src/pattern_reader.cpp)

# 添加测试
add_test(NAME test_algorithms COMMAND test_algorithms)
add_test(NAME test_pattern_reader COMMAND test_pattern_reader)

