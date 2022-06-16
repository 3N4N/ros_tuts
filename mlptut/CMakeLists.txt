cmake_minimum_required(VERSION 2.8.3)
project(mlptut)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy)

## Declare a catkin package
catkin_package()


## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(mlp src/minimal.cpp)
target_link_libraries(mlp ${catkin_LIBRARIES})

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(mlp ${PYTHON_LIBRARIES})
