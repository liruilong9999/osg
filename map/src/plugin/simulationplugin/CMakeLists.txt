# 引入外部函数
include(${ROOT_DIR}/cmake/module.cmake)

# 获取文件名称
set(AbsolutePathProject ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(ProjectName ${AbsolutePathProject} NAME)

# Qt 库
set(QT_LIBRARY_LIST "Core" "Gui" "Widgets" )

# 链接osg库
#set(OSG_LIBRARY_LIST osgDB osgGA osgViewer osg OpenThreads osgFX osgUtil osgQOpenGL osgSim osgParticle osgManipulator osgEarth)

# 链接库
set(SELF_LIBRARY_LIST "lbase" "mapbase")

# 预编译
add_compile_definitions(SIMULATIONPLUGIN_LIBRARY) 

# 创建项目
CreateTarget(${ProjectName} "Dll" "Plugin") 
   