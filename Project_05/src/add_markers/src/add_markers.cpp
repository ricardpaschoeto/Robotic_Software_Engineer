#include <ros/ros.h>
#include <stdlib.h> 
#include <visualization_msgs/Marker.h>
#include <iostream>
#include "nav_msgs/Odometry.h"

using namespace std;

class add_markers
{
private:
	ros::NodeHandle n;
	ros::Subscriber sub;
	ros::Publisher marker_pub;
	visualization_msgs::Marker marker;
	uint32_t shape;
	double x_pickup;
	double y_pickup;
	double x_dropoff;
	double y_dropoff;
	bool pickup;
public:
	add_markers(){

		x_pickup = -1.0;
		y_pickup = -1.0;
		x_dropoff = 0.5;
		y_dropoff = 0.5;

		// Set our initial shape type to be a cube
		shape = visualization_msgs::Marker::CUBE;

		// x and y coordinates for pickup and dropoff zones respectively
		marker.pose.position.x = x_pickup;
		marker.pose.position.y = y_pickup;

		// Set the frame ID and timestamp.  See the TF tutorials for information on these.
		marker.header.frame_id = "/map";
		marker.header.stamp = ros::Time::now();

		// Set the namespace and id for this marker.  This serves to create a unique ID
		// Any marker sent with the same namespace and id will overwrite the old one
		marker.ns = "add_markers";
		marker.id = 0;

		// Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
		marker.type = shape;

		// Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
		marker.action = visualization_msgs::Marker::ADD;

		// Set the scale of the marker -- 1x1x1 here means 1m on a side
		marker.scale.x = 0.5;
		marker.scale.y = 0.5;
		marker.scale.z = 0.5;

		// Set the color -- be sure to set alpha to something non-zero!
		marker.color.r = 0.0f;
		marker.color.g = 1.0f;
		marker.color.b = 0.0f;
		marker.color.a = 1.0;

		marker.lifetime = ros::Duration();

		pickup = false;
		sub = n.subscribe("odom", 1000, &add_markers::chatterCallback, this);
		marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
	}

	void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg){

		double vel_x = msg->twist.twist.linear.x;
		double ang_z = msg->twist.twist.angular.z;

		ROS_INFO("I heard vel_x: [%f]", vel_x);
		ROS_INFO("I heard ang_z: [%f]", ang_z);

		marker_pub.publish(marker);

		if (abs(vel_x) < 1e-5 && abs(ang_z) < 1e-4){
		   
                   if (!pickup){
		   	marker.action = visualization_msgs::Marker::DELETE;
			marker_pub.publish(marker);
			pickup = true;
			// Waiting the robot start to move.
			ros::Duration(7.0).sleep();
		   }else{
			if (abs(vel_x) < 4e-6){
			   	marker.pose.position.x = x_dropoff;
			   	marker.pose.position.y = y_dropoff;
				marker.action = visualization_msgs::Marker::ADD;
				marker_pub.publish(marker);
			}
		   }
		   
		}
	}
};

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  add_markers markers;
  
  ros::spin();

  return 0;
}
