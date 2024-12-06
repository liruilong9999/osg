# 引入外部函数
include(${ROOT_DIR}/cmake/module.cmake)

# 获取文件名称
set(AbsolutePathProject ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(ProjectName ${AbsolutePathProject} NAME)
# Qt 库
# set(QT_LIBRARY_LIST "Core" "Gui" "Widgets" )

# 链接库
#set(SELF_LIBRARY_LIST "CPlusPlusReflection")
# 预编译
add_compile_definitions(LBASEGRAPH_LIBRARY)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR}/../bin/lib) # .lib and .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR}/../bin/lib) # .so and .dylib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR}/../bin) # .exe and .dll
set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR}/../bin/lib) # .lib and .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR}/../bin/lib) # .so and .dylib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR}/../bin) # .exe and .dll
# 创建项目
CreateTarget(${ProjectName} "Dll")
