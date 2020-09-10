#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg){
    ROS_INFO("Angle Minimum:[%f]", msg->angle_min);
    ROS_INFO("Angle Increment:[%f]", msg->angle_increment);
    
    std::vector<float> temp;

    std::copy(&msg->ranges[0],&msg->ranges[579], std::back_inserter(temp));

    for (int i =0; i < sizeof(temp); i++){
        ROS_INFO("Hearing:[%f]", temp[i]);
    }
    
    //ROS_INFO("Hearing:[%f]", msg->ranges);
}

int main(int argc, char **argv){
    ros::init(argc,argv, "listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("front/scan", 1000, chatterCallback);
    ros::spin();
    return 0;
}