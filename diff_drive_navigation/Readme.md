## Run
```sh
# Building Project
$ cd ~/catkin_ws/src
$ git clone <project URL>
$ cd ../
$ catkin_make


# Running Project
$ roslaunch differential_drive diff_drive.launch
$ rosrun teleop_twist_keyboard teleop_twist_keyboard.py
or
$ rosrun differential_drive teleop_twist_keyboard


# Start mapping

$ roslaunch diff_drive_navigation mapping.launch
$ rviz # for visualization

# Storing Map
$ rosrun map_server map_saver -f mymap


# Autonomous Nav
$ roslaunch diff_drive_navigation navigation.launch


```

## Dependencies Install
```sh
# gmapping
$ sudo apt-get install ros-noetic-gmapping

# Teleop keyboard
$ sudo apt-get install ros-noetic-teleop-twist-keyboard

# Map Server
$ sudo apt-get install ros-noetic-map-server

# Movebase
$ sudo apt-get install ros-noetic-move-base

# Global Planner
$ sudo apt-get install ros-noetic-global-planner

# Local Planner
$ sudo apt-get install ros-noetic-teb-local-planner // dwa-local-planner

# AMCL for localization
$ sudo apt-get install ros-noetic-amcl

#

```
