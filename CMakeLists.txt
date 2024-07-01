# 设置项目的最低CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 项目信息
project(IDS VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定项目的源文件
set(SOURCE_FILES
    src/main.cpp
    src/pattern_reader.cpp
    src/pcap_handler.cpp
    src/matcher.cpp
    src/algorithms/brute_force.cpp
    src/algorithms/kmp.cpp
    src/algorithms/boyer_moore.cpp
)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/algorithms)

# 添加可执行文件
add_executable(main ${SOURCE_FILES})

# 手动查找 Pcap 库
find_path(PCAP_INCLUDE_DIR pcap.h)
find_library(PCAP_LIBRARY pcap)

if (PCAP_INCLUDE_DIR AND PCAP_LIBRARY)
    set(PCAP_FOUND TRUE)
    include_directories(${PCAP_INCLUDE_DIR})
    target_link_libraries(main ${PCAP_LIBRARY})
else()
    message(FATAL_ERROR "Pcap library not found")
endif()

# 启用测试
enable_testing()

# 添加综合测试文件
add_executable(test_algorithms tests/test_algorithms.cpp src/algorithms/brute_force.cpp src/algorithms/kmp.cpp src/algorithms/boyer_moore.cpp)

# 添加测试
add_test(NAME test_algorithms COMMAND test_algorithms)

# 注释掉其他测试文件
# add_executable(test_pattern_reader tests/test_pattern_reader.cpp src/pattern_reader.cpp)
# add_executable(test_pcap_handler tests/test_pcap_handler.cpp src/pcap_handler.cpp src/matcher.cpp src/algorithms/brute_force.cpp src/algorithms/kmp.cpp src/algorithms/boyer_moore.cpp)
# add_executable(test_matcher tests/test_matcher.cpp src/matcher.cpp src/pattern_reader.cpp src/algorithms/brute_force.cpp src/algorithms/kmp.cpp src/algorithms/boyer_moore.cpp)

# 链接测试用的 pcap 库
# target_link_libraries(test_pcap_handler ${PCAP_LIBRARY})
# target_link_libraries(test_pattern_reader ${PCAP_LIBRARY})
# target_link_libraries(test_matcher ${PCAP_LIBRARY})

# 添加测试
# add_test(NAME test_pattern_reader COMMAND test_pattern_reader)
# add_test(NAME test_pcap_handler COMMAND test_pcap_handler)
# add_test(NAME test_matcher COMMAND test_matcher)
