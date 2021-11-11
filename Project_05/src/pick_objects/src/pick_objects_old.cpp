#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send pickup_goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient_pickup;
// Define a client for to send dropoof_goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient_dropoff;

int main(int argc, char** argv){

  double x_pickup = -1.0;
  double y_pickup = -1.0;

  double x_dropoff = 0.5;
  double y_dropoff = 0.5;

  // Initialize the multiple_navigation_goals node
  ros::init(argc, argv, "multiple_navigation_goals");

  //tell the pickup action client that we want to spin a thread by default
  MoveBaseClient_pickup acp("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!acp.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base pick up action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup_goal;

  // set up the frame parameters
  pickup_goal.target_pose.header.frame_id = "map";
  pickup_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pickup_goal.target_pose.pose.position.x = x_pickup;
  pickup_goal.target_pose.pose.position.y = y_pickup;
  pickup_goal.target_pose.pose.orientation.w = -1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  acp.sendGoal(pickup_goal);

  // Wait an infinite time for the results
  acp.waitForResult();

  // Check if the robot reached its goal
  if(acp.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved 1.0 meters backward");
    ros::Duration(5.0).sleep();
  }else{
    ROS_INFO("The base failed to move backward 1.0 meters for some reason");
  }

  // ############################################################################

  //tell the drop off action client that we want to spin a thread by default
  MoveBaseClient_dropoff acd("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!acd.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base pick up action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup_dropoff;

  // set up the frame parameters
  pickup_dropoff.target_pose.header.frame_id = "map";
  pickup_dropoff.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pickup_dropoff.target_pose.pose.position.x = x_dropoff;
  pickup_dropoff.target_pose.pose.position.y = y_dropoff;
  pickup_dropoff.target_pose.pose.orientation.w = 1.0;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  acd.sendGoal(pickup_dropoff);

  // Wait an infinite time for the results
  acd.waitForResult();

  // Check if the robot reached its goal
  if(acd.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved 0.5 meters forward");
    ros::Duration(5.0).sleep();
  }
  else{
    ROS_INFO("The base failed to move forward 0.5 meters for some reason");
  }

  return 0;
}
