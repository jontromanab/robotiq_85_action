#!/usr/bin/env python



import rospy, actionlib
import thread

from control_msgs.msg import GripperCommandAction
from robotiq_85_msgs.msg import GripperCmd
from std_msgs.msg import Float32, Bool
from math import asin

class ParallelGripperActionController:
   
    def __init__(self):
        rospy.init_node('gripper')
       
       
        self.r_pub = rospy.Publisher('gripper/cmd', GripperCmd, queue_size=10)

        # subscribe to command and then spin
        self.server = actionlib.SimpleActionServer('~gripper_action', GripperCommandAction, execute_cb=self.actionCb, auto_start=False)
        self.server.start()
        rospy.spin()

    def actionCb(self, goal):
        """ Take an input command of width to open gripper. """
        rospy.loginfo('Gripper controller action goal recieved:%f' % goal.command.position)
        command = goal.command.position
        
        # publish msgs
        
        
        cmsg = GripperCmd();
	pos = command;
	if pos>0.08:
	    cmsg.position = 0.08 - pos/10;
	else:
	    cmsg.position = 0.08 - pos;
        #cmsg.position = 0.8 - command
        cmsg.speed = 0.06
        cmsg.force = 100.0
        cmsg.emergency_release = bool(0)
        #cmsg.emergency_release_dir = 0
	#cmsg.stop = 0
        
        self.r_pub.publish(cmsg)
        rospy.sleep(5.0)
        self.server.set_succeeded()
        rospy.loginfo('Gripper Controller: Done.')

if __name__=='__main__': 
    try:
        ParallelGripperActionController()
    except rospy.ROSInterruptException:
        rospy.loginfo('Hasta la Vista...')
        

