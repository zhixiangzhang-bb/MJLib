# CMakeList.txt: MachineLearning 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)





# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()




project ("MJLib")



#添加子库
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJLib_Net)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJLib_CNN)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJLib_DataProcess)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJLib_FileIO)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJLib_SVM)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJLib_Vision)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJLib_Camera)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/MJLib_Log)
include_directories(${CMAKE_SOURCE_DIR}/src/MJLIB_DataProcess/include)

#包含头文件
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/Eigen)
#include_directories(${CMAKE_SOURCE_DIR}/src/MJLib_CNN)
include_directories(${CMAKE_SOURCE_DIR}/src/MJLib_DataProcess)
include_directories(${CMAKE_SOURCE_DIR}/src/MJLib_FileIO)
include_directories(${CMAKE_SOURCE_DIR}/src/MJLib_SVM)
include_directories(${CMAKE_SOURCE_DIR}/src/MJLib_Vision)
include_directories(${CMAKE_SOURCE_DIR}/src/MJLib_Net)

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/snap7/core)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/snap7/lib)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/snap7/sys)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/snap7)

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/FFTW/include)

add_executable (${PROJECT_NAME} 
		${CMAKE_CURRENT_SOURCE_DIR}/src/Test.cpp
)		





set(CMAKE_DEBUG_POSTFIX "d")



#target_link_libraries(${PROJECT_NAME} PRIVATE  MJLib_CNN)
target_link_libraries(${PROJECT_NAME} PRIVATE  MJLib_DataProcess)
target_link_libraries(${PROJECT_NAME} PRIVATE  MJLib_FileIO)
target_link_libraries(${PROJECT_NAME} PRIVATE  MJLib_SVM)
target_link_libraries(${PROJECT_NAME} PRIVATE  MJLib_Vision)
target_link_libraries(${PROJECT_NAME} PRIVATE  MJLib_Net)




if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
