#!/bin/sh

export TURTLEBOT_GAZEBO_WORLD_FILE=/home/workspace/catkin_ws/src/map/my_world.world
export TURTLEBOT_GAZEBO_MAP_FILE=/home/workspace/catkin_ws/src/map/map.yaml

xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 3
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 3
xterm -e " roslaunch pick_objects pick_objects.launch" &
sleep 3
xterm -e " roslaunch add_markers add_markers.launch" 