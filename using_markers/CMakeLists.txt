cmake_minimum_required(VERSION 3.0.2)
project(using_markers)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  visualization_msgs
  interactive_markers
  tf
)

catkin_package()
include_directories(include ${catkin_INCLUDE_DIRS})



add_executable(basic_shapes src/basic_shapes.cc)
target_link_libraries(basic_shapes ${catkin_LIBRARIES})

add_executable(points_and_lines src/points_lines.cc)
target_link_libraries(points_and_lines ${catkin_LIBRARIES})

add_executable(simple_marker src/simple_marker.cc)
target_link_libraries(simple_marker ${catkin_LIBRARIES})

add_executable(basic_controls src/basic_controls.cc)
target_link_libraries(basic_controls ${catkin_LIBRARIES})
# add_dependencies(basic_shapes basic_controls_generate_messages_cpp)
