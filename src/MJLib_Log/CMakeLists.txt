# CMakeList.txt: MJLib_Siemens 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)




# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()




project ("MJLib_Log")


include_directories(${CMAKE_SOURCE_DIR}/3rdparty/glog/include)


set(CMAKE_DEBUG_POSTFIX "d")



#设置项目文件
set(PROJECT_SOURCES
    mjlib_log_api.cpp
	mjlib_log_api.h
	mjlib_log_global.h
	mjlib_log_test.cpp
	mjlib_log_core.h
	mjlib_log_core.cpp
)


if(CMAKE_BUILD_TYPE STREQUAL "Release")

add_library (${PROJECT_NAME} SHARED
	${PROJECT_SOURCES})
else()

# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME}  
	${PROJECT_SOURCES}
)

endif()





#判断编译器位数执行不同链接操作
if(CMAKE_CL_64)    
	target_link_libraries(${PROJECT_NAME}  PRIVATE 
	${CMAKE_SOURCE_DIR}/3rdparty/glog/lib/x64/glogd.lib
)
else()
	target_link_libraries(${PROJECT_NAME}  PRIVATE 
	${CMAKE_SOURCE_DIR}/3rdparty/glog/lib/x86/glogd.lib
)
endif()


add_compile_definitions(${PROJECT_NAME})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
