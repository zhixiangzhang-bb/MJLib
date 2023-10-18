# CMakeList.txt: zlib_DataProcess 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)




# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()



project ("MJLib_DataProcess")




include_directories(${CMAKE_SOURCE_DIR}/3rdparty/Eigen)




set(CMAKE_DEBUG_POSTFIX "d")





# 将源代码添加到此项目的可执行文件。
add_library (${PROJECT_NAME}  SHARED
	mjlib_dataprocess_macro.h
	mjlib_dataprocess_test.cpp
	mjlib_frequencydomain.h
	mjlib_frequencydomain.cpp
	mjlib_timedomain.h
	mjlib_timedomain.cpp
	mjlib_dataprocess_api.h
	mjlib_dataprocess_api.cpp
	)





add_compile_definitions(${PROJECT_NAME})



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
