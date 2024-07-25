cmake_minimum_required(VERSION 3.10)
project(IDS)

set(CMAKE_CXX_STANDARD 14)

# 添加源文件
set(SOURCES
    src/main.cpp
    src/pattern_reader.cpp
    src/pcap_handler.cpp
    src/firewall.cpp
    src/matcher.cpp
    src/algorithms/brute_force.cpp
    src/algorithms/kmp.cpp
    src/algorithms/boyer_moore.cpp
)

# 添加头文件目录
include_directories(src)
include_directories(src/algorithms)

# 生成主可执行文件
add_executable(main ${SOURCES})

# 链接 libpcap 库
target_link_libraries(main pcap)

# 启用测试
enable_testing()

# 添加测试源文件
set(TEST_SOURCES
    src/pattern_reader.cpp
    src/algorithms/brute_force.cpp
    src/algorithms/kmp.cpp
    src/algorithms/boyer_moore.cpp
    src/matcher.cpp
    src/pcap_handler.cpp
    src/firewall.cpp
)

# 包含测试所需的头文件目录
include_directories(tests)

# 添加测试可执行文件
add_executable(test_algorithms tests/test_algorithms.cpp ${TEST_SOURCES})
add_executable(test_pattern_reader tests/test_pattern_reader.cpp ${TEST_SOURCES})
add_executable(test_pcap_handler tests/test_pcap_handler.cpp ${TEST_SOURCES})

# 链接 libpcap 库到测试程序
target_link_libraries(test_algorithms pcap)
target_link_libraries(test_pattern_reader pcap)
target_link_libraries(test_pcap_handler pcap)

# 注册测试
add_test(NAME AlgorithmsTest COMMAND test_algorithms)
add_test(NAME PatternReaderTest COMMAND test_pattern_reader)
add_test(NAME PCAPHandlerTest COMMAND test_pcap_handler)

