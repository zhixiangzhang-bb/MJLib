﻿# CMakeList.txt: MJLib_Siemens 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)




# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()




project ("MJLib_Siemens")




set(CMAKE_DEBUG_POSTFIX "d")





include_directories(${CMAKE_SOURCE_DIR}/3rdparty/snap7/core)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/snap7/lib)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/snap7/sys)



# 将源代码添加到此项目的可执行文件。
add_library (${PROJECT_NAME}  SHARED
	mjlib_siemensclient.cpp 
	mjlib_siemensclient.h
	mjlib_siemens_api.h
	mjlib_siemens_global.h
	mjlib_siemens_test.cpp
)


#判断编译器位数执行不同链接操作
if(CMAKE_CL_64)    
	target_link_libraries(${PROJECT_NAME}  PRIVATE 
	D:/Work/Clibrary/snap7-full-1.4.2/release/Windows/Win64/snap7.lib
)
else()
	target_link_libraries(${PROJECT_NAME}  PRIVATE 
	D:/Work/Clibrary/snap7-full-1.4.2/release/Windows/Win64/snap7.lib
)

endif()

add_compile_definitions(${PROJECT_NAME})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MJLib_Siemens PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
