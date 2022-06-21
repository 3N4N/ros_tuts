cmake_minimum_required(VERSION 3.0.2)
project(diff_drive_navigation)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  gazebo_ros
  std_msgs
  geometry_msgs
  sensor_msgs
  nav_msgs
)

find_package(gazebo REQUIRED)

catkin_package(
  CATKIN_DEPENDS
  roscpp
  std_msgs
  geometry_msgs
  sensor_msgs
  nav_msgs
)


add_executable(
  teleop_twist_keyboard
  src/teleop_twist_keyboard.cpp
)

target_link_libraries(teleop_twist_keyboard ${catkin_LIBRARIES})


link_directories(${GAZEBO_LIBRARY_DIRS})

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${src}
  ${GAZEBO_INCLUDE_DIRS}
)


link_directories(${GAZEBO_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")
