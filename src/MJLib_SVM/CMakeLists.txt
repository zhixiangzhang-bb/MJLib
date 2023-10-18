# CMakeList.txt: zlib_SVM 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MJLib_SVM")


include_directories(${CMAKE_SOURCE_DIR}/3rdparty/onnxruntime/include)



# 将源代码添加到此项目的可执行文件。



# 生成库
add_library (${PROJECT_NAME} SHARED
	mjlib_svm_api.h
	mjlib_svm_api.cpp
	mjlib_svm_macro.h
	mjlib_svm.h
	mjlib_svm.cpp
	mjlib_test.cpp
	)




set(CMAKE_DEBUG_POSTFIX "d")







#判断编译器位数执行不同链接操作
if(CMAKE_CL_64)    
	target_link_libraries(${PROJECT_NAME}  PRIVATE 
	${CMAKE_SOURCE_DIR}/3rdparty/onnxruntime/x64/lib/onnxruntime.lib
)

else()
	target_link_libraries(${PROJECT_NAME}  PRIVATE 
	${CMAKE_SOURCE_DIR}/3rdparty/onnxruntime/x86/lib/onnxruntime.lib
	)

endif()







if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
