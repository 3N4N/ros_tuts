cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

find_package(Qt5 REQUIRED
    Core
    PrintSupport
    Gui
    Widgets
)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

# New in gazebo6: c++11 flags are now required
# for all downstream software to compile against gazebo.
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(hello_world SHARED src/hello_world.cc)
target_link_libraries(hello_world ${GAZEBO_LIBRARIES})

add_library(model_push SHARED src/model_push.cc)
target_link_libraries(model_push ${GAZEBO_LIBRARIES})

add_library(factory SHARED src/factory.cc)
target_link_libraries(factory ${GAZEBO_LIBRARIES})

add_library(system_gui SHARED src/system_gui.cc)
target_link_libraries(system_gui ${GAZEBO_LIBRARIES})

add_library(world_edit SHARED src/world_edit.cc)
target_link_libraries(world_edit ${GAZEBO_LIBRARIES})

add_library(sysplug_mouse SHARED src/sysplug_mouse.cc)
target_link_libraries(sysplug_mouse ${GAZEBO_LIBRARIES} Qt5::Widgets)
