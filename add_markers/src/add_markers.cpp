#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    initial = true;
    picked = false;
    dropped = false;
    marker_pub = n_.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    odom_sub = n_.subscribe("/odom", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const nav_msgs::Odometry odom_data)
  {
    double xPose = odom_data.pose.pose.position.x;
    double yPose = odom_data.pose.pose.position.y;
    
    uint32_t shape = visualization_msgs::Marker::CUBE;
    visualization_msgs::Marker marker;
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "basic_shapes";
    marker.id = 0;
    marker.type = shape;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();
    
    while (marker_pub.getNumSubscribers() < 1)
    {
      sleep(1);
    }
    
    if (initial && !picked && !dropped) {
      initial = false;
      marker.pose.position.x = -3.3;
      marker.pose.position.y = 1.3;
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
    }
    
    if ((pow(xPose + 3.3, 2) + pow(yPose - 1.3, 2) < 0.06) && !initial && !picked && !dropped) {
      ROS_INFO("Object is picked up.");
      picked = true;
      marker.pose.position.x = -3.3;
      marker.pose.position.y = 1.3;
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      ros::Duration(5).sleep();
    }
    
    if ((pow(xPose - 1.6, 2) + pow(yPose - 1.7, 2) < 0.06) && !initial && picked && !dropped) {
      ROS_INFO("Object is dropped off.");
      dropped = true;
      marker.pose.position.x = 1.75;
      marker.pose.position.y = 1.65;
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
    }
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher marker_pub;
  ros::Subscriber odom_sub;
  bool initial;
  bool picked;
  bool dropped;
};


int main( int argc, char** argv )
{
  ros::init(argc, argv, "subscribe_and_publish");
  SubscribeAndPublish SAPObject;
  ros::spin();
  return 0;
}