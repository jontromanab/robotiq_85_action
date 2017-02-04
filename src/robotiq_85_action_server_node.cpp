#include <ros/ros.h>
#include <robotiq_85_action/robotiq_85_action_server.h>

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "gripper");

  GripperAction ga;

  ros::spin();
}
