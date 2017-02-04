#include<robotiq_85_action/robotiq_85_action_server.h>

GripperAction::GripperAction() : privateNode("~"),
  asGripperCommand(privateNode, "gripper_action", boost::bind(&GripperAction::executeGripperCommand, this, _1), false)
{
  std::string gripperCommandTopic("/gripper/cmd");
  std::string gripperStatusTopic("/gripper/stat");
  privateNode.getParam ("gripper_command_topic", gripperCommandTopic);
  privateNode.getParam ("gripper_status_topic", gripperStatusTopic);

  gripperCmdPublisher = nh.advertise<robotiq_85_msgs::GripperCmd>(gripperCommandTopic, 1);
  gripperStatusSubscriber = nh.subscribe(gripperStatusTopic, 1, &GripperAction::gripperStatusCallback, this);

  asGripperCommand.start ();
}

void GripperAction::gripperStatusCallback (const robotiq_85_msgs::GripperStat msg)
{
  gripperStatus = msg;
}

void GripperAction::executeGripperCommand (const control_msgs::GripperCommandGoalConstPtr &goal)
{
  control_msgs::GripperCommandResult result;

  robotiq_85_msgs::GripperCmd cmd;
  cmd.emergency_release = false;
  cmd.stop = false;
  float pos = goal->command.position;
  if(pos > 0.08)
	cmd.position = 0.08 - pos/10;
  else
	cmd.position = 0.08 - pos;
  //cmd.position = (goal->command.position)/10;
  cmd.speed = defaultGripperSpeed;
  cmd.force = goal->command.max_effort;
  gripperCmdPublisher.publish(cmd);


  ros::Rate loopRate(30);
  bool positionReached = false;
  bool gripperStopped = false;
  ros::Duration(0.25).sleep ();
  while(!(positionReached || gripperStopped))
  {
    gripperStopped = !gripperStatus.is_moving;
    positionReached = fabs(gripperStatus.position - cmd.position) < 0.001;
    loopRate.sleep ();
  }

  cmd.stop  = true;
  gripperCmdPublisher.publish(cmd);

  result.position = gripperStatus.position;
  result.reached_goal = positionReached;
  asGripperCommand.setSucceeded (result);
}



