# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("CMake_test1")

# 项目message信息
message(STATUS "This is BINARY dir: " ${CMake_test1_BINARY_DIR})  #CMake_test1_BINARY_DIR == PROJECT_BINARY_DIR bulid
message(STATUS "This is SOURCE dir: " ${CMake_test1_SOURCE_DIR})  #CMake_test1_SOURCE_DIR == PROJECT_SOURCE_DIR source

# The version number. 版本号
set (HELLOWORLD_VERSION_MAJOR 1)
set (HELLOWORLD_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code  从源目录的.in配置来生成.h头文件（该例为生成版本号的.h文件） 文件→生成目标文件
configure_file ("${PROJECT_SOURCE_DIR}/HelloWorld/helloworldConfig.h.in" "${PROJECT_SOURCE_DIR}/HelloWorld/helloworldConfig.h")
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
message(STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})

# 包含子项目。
add_subdirectory ("HelloWorld")

# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# add the MyMathFunctions library?
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MyMathFunctions")
  add_subdirectory (MyMathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MyMathFunctions)
endif ()

