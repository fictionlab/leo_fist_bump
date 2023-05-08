cmake_minimum_required(VERSION 3.0.2)
project(bump)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES bump
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(bump_node src/bump_node.cpp)

add_dependencies(bump_node ${bump_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(bump_node
  ${catkin_LIBRARIES}
)