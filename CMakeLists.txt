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
)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/src)

# 添加可执行文件
add_executable(main ${SOURCE_FILES})

# 链接pcap库
find_package(Pcap REQUIRED)
if (Pcap_FOUND)
    include_directories(${Pcap_INCLUDE_DIRS})
    target_link_libraries(main ${Pcap_LIBRARIES})
else()
    message(FATAL_ERROR "Pcap library not found")
endif()

# 测试配置
enable_testing()

# 添加测试文件
add_executable(test_pattern_reader tests/test_pattern_reader.cpp src/pattern_reader.cpp)
add_executable(test_pcap_handler tests/test_pcap_handler.cpp src/pcap_handler.cpp src/matcher.cpp)
add_executable(test_matcher tests/test_matcher.cpp src/matcher.cpp src/pattern_reader.cpp)

# 链接测试用的 pcap 库
target_link_libraries(test_pcap_handler ${Pcap_LIBRARIES})
target_link_libraries(test_pattern_reader ${Pcap_LIBRARIES})
target_link_libraries(test_matcher ${Pcap_LIBRARIES})

# 添加测试
add_test(NAME test_pattern_reader COMMAND test_pattern_reader)
add_test(NAME test_pcap_handler COMMAND test_pcap_handler)
add_test(NAME test_matcher COMMAND test_matcher)
