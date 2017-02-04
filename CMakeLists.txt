cmake_minimum_required(VERSION 2.8.3)
project(robotiq_85_action)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp actionlib control_msgs)




###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${robotiq_85_action_INCLUDE_DIRS}
  )


## Declare a cpp executable
add_executable(robotiq_85_action_server src/robotiq_85_action_server.cpp src/robotiq_85_action_server_node.cpp)
## Specify libraries to link a library or executable target against
target_link_libraries(robotiq_85_action_server
  ${catkin_LIBRARIES}
)
## Add cmake target dependencies of the executable/library
add_dependencies(robotiq_85_action_server control_msgs)

add_executable(client_test src/robotiq_85_action_client_test.cpp)
add_dependencies(client_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(client_test ${catkin_LIBRARIES})



#install(TARGETS robotiq_85_action_server
 #ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
 #LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
 
#)

#install(DIRECTORY include/${PROJECT_NAME}/
 #DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#)

## Mark cpp header files for installation
#install(DIRECTORY include/${PROJECT_NAME}/
   #DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   #FILES_MATCHING PATTERN "*.h"
   #PATTERN ".svn" EXCLUDE
 #)



