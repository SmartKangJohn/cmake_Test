# cmake_Test
使用cmake实现跨平台编程功能，如windows vs编程c++ → linux gdb c++

## helloworld 例
### ※ PROJECT指令
语法：PROGECT(projectname [CXX] [C] [Java])
可以用这个指令定义工程名称，支持的语言列表是可以忽略的，默认情况下就是表示支持所有的语言。
这个指令隐式地定义了两个Cmake变量：
<projectname>_BINARY_DIR以及<projectname>_SOURCE_DIR。在本实验中就是HELLO_BINARY_DIR/HELLO_SOURCE_DIR。所以下联的两个MESSAGE指令可以直接调用这两个变量。
### ※ MESSAGE指令
语法：MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display"...)
这个指令用于向终端输出用户定义的信息，包含了三种类型:
SEND_ERROR，产生错误，生成过程被跳过
SATUS，输出前缀为-的信息
FATAL_ERROR，立即终止所有 cmake 过程
这里使用的是 STATUS 信息输出，演示了由 PROJECT 指令定义的两个隐式变量HELLO_BINARY_DIR 和 HELLO_SOURCE_DIR。
### ※ ADD_EXECUTABLE指令
ADD_EXECUTABLE(HELLO  ${SRC_LIST})定义了这个工程会生成一个文件名为
	HELLO的可执行文件，相关的源文件是 SRC_LIST 中定义的源文件列表， 本例中可以直接写成 ADD_EXECUTABLE(HELLO  main.c)

## cmake版本号配置与头文件生成
set (HELLOWORLD_VERSION_MAJOR 1)
configure_file ("${PROJECT_SOURCE_DIR}/HelloWorld/helloworldConfig.h.in" "${PROJECT_BINARY_DIR}/HelloWorld/helloworldConfig.h")
include_directories("${PROJECT_BINARY_DIR}/HelloWorld")

## 添加一个库
add_library(MathFunctions mysqrt.cxx)
cmakedefine USE_MYMATH   //CMakeConfig.h.in
option(USE_MYMATH "Use tutorial provided math implementation" ON)
add_library(MathFunctions mysqrt.c)
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif ()
target_link_libraries (Tutorial  ${EXTRA_LIBS})

## 安装与测试
添加安装规则install rules和测试支持testing support
当前层：
	install (TARGETS MathFunctions DESTINATION bin)
	install (FILES MathFunctions.h DESTINATION include)
顶层：
	# add the install targets
	install (TARGETS Tutorial DESTINATION bin)
	install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

## 常用基本命令
1. cmake_minimum_required(VERSION 2.8)  ///检查cmake的版本，至少为2.8
2. PROJECT(helloworld)    ///工程名为helloworld
# 通过在主工程文件CMakeLists.txt中修改ADD_SUBDIRECTORY (lib) 指令来指定一个编译输出位置;
# 指定本工程中静态库libhello.so生成的位置，即 build/lib;
ADD_SUBDIRECTORY(lib)
3. aux_source_directory(.  SRC_LIST) ///查找当前目录下所有的源文件并保存到SRC_LIST变量中
4.INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include   ${PROJECT_SOURCE_DIR}/abc)  ///将根目录下的include和abc加入包含目录列表
5. LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)  ///将 ./lib加入编译器链接阶段的搜索目录列表
6. add_executable(hello  $(SRC_LIST})  ///使用SRC_LIST源文件列表里的文件生成一个可执行文件hello
如：add_executable(hello main.cpp base.cpp base.h)  
7. add_library(hello STATIC ${SRC_LIST})   使用SRC_LIST源文件列表里的文件生成一个静态链接libhello.a
ADD_LIBRARY (base STATIC ${SRC_LIST})
8. add_library(hello SHARD ${SRC_LIST})   使用SRC_LIST源文件列表里的文件生成一个动态链接库libhello.so
9. target_link_libraries(hello a b.a c.so) /// 将若干库文件链接到目标hello中，target_link_libraries里的库文件的顺序符合gcc/g++链接顺序的规则，即被依赖的库放在依赖它的库的后面，如果顺序有错，链接时会报错。