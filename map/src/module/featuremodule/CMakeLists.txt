# 引入外部函数
include(${ROOT_DIR}/cmake/module.cmake)
#include(${ROOT_DIR}/cmake/module_osg.cmake)  # 包含自定义的 OSG 配置文件

# 获取文件名称
set(AbsolutePathProject ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(ProjectName ${AbsolutePathProject} NAME)
# Qt 库
set(QT_LIBRARY_LIST "Core")

# 链接osg库
set(OSG_LIBRARY_LIST osgDB osgGA osgViewer osg OpenThreads osgFX osgUtil osgQOpenGL osgSim osgParticle osgManipulator osgEarth)

# 链接自身库
set(SELF_LIBRARY_LIST "lbase")


# 预编译
add_compile_definitions(FEATUREMODULE_LIBRARY)

# 创建项目 
CreateTarget(${ProjectName} "Dll")  
