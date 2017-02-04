#ifndef ROBOTIQ_85_ACTION_SERVER_H
#define ROBOTIQ_85_ACTION_SERVER_H

#include<ros/ros.h>
#include<actionlib/client/simple_action_client.h>
#include<actionlib/server/simple_action_server.h>
#include<control_msgs/GripperCommandAction.h>
#include<robotiq_85_msgs/GripperCmd.h>
#include<robotiq_85_msgs/GripperStat.h>

class GripperAction
{
public:
  GripperAction();
private:
  void executeGripperCommand(const control_msgs::GripperCommandGoalConstPtr &goal);
  void gripperStatusCallback(const robotiq_85_msgs::GripperStat msg);


  //constants
  static const float defaultGripperSpeed = 0.013;
  static const float defaultGripperForce = 100;
  static const float gripperClosedPosition = 0;
  static const float gripperOpenPosition = 0.085;
  static const float gripperMinSpeed = 0.013;
  static const float gripperMinForce = 5;

  ros::NodeHandle nh, privateNode;

  //Messages
  ros::Publisher gripperCmdPublisher;
  ros::Subscriber gripperStatusSubscriber;

  //Actionlib
  actionlib::SimpleActionServer<control_msgs::GripperCommandAction> asGripperCommand;

  //Gripper Status
  robotiq_85_msgs::GripperStat gripperStatus;
};


#endif // ROBOTIQ_85_ACTION_SERVER_H
