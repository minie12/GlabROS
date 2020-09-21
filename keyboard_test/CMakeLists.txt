cmake_minimum_required(VERSION 3.0.2)
project(keyboard_test)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  turtlesim
  tf
)

## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES keyboard_test
  CATKIN_DEPENDS roscpp std_msgs turtlesim tf
  DEPENDS system_lib
)

###########
## Build ##
###########
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(listener_node src/listener.cpp)
add_executable(keyboard_node src/keyboard_test_node.cpp)
add_executable(turtle_listener_node src/turtle_listener.cpp)
add_executable(turtle_broadcaster_node src/turtle_broadcaster.cpp)
add_executable(robot_control_node src/robot_control.cpp)
add_executable(keyboard_collision_node src/laser_listener.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(listener_node ${catkin_LIBRARIES})
target_link_libraries(keyboard_node ${catkin_LIBRARIES})
target_link_libraries(turtle_listener_node ${catkin_LIBRARIES})
target_link_libraries(turtle_broadcaster_node ${catkin_LIBRARIES})
target_link_libraries(robot_control_node ${catkin_LIBRARIES})
target_link_libraries(keyboard_collision_node ${catkin_LIBRARIES})

