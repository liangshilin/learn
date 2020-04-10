
# 声明cmake最低版本
cmake_minimum_required (VERSION 3.8)

# cmake工程命名
project (learn_unix CXX)

# 日志输出
message (status "cmake start...")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# include头文件之类
include_directories ( 
${PROJECT_SOURCE_DIR}/algorithm
${PROJECT_SOURCE_DIR}/datastruct
${PROJECT_SOURCE_DIR}/stl
)

# 汇总源代码文件给变量SRC
set (SRC 
${PROJECT_SOURCE_DIR}/algorithm/array.hpp
${PROJECT_SOURCE_DIR}/algorithm/interesting.hpp
${PROJECT_SOURCE_DIR}/algorithm/list.hpp
${PROJECT_SOURCE_DIR}/algorithm/sort.hpp
${PROJECT_SOURCE_DIR}/algorithm/str.hpp
${PROJECT_SOURCE_DIR}/datastruct/binary_tree.hpp
${PROJECT_SOURCE_DIR}/stl/containers.hpp
)
# 创建静态库
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set (LIB_NAME learn_lib)

add_library (${LIB_NAME} STATIC ${SRC})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable (${PROJECT_NAME} learn.cpp ${SRC})

target_link_libraries (${PROJECT_NAME} ${LIB_NAME})
