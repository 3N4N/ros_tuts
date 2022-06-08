#include "ros/ros.h"
#include "std_msgs/String.h"


// why use constptr? works fine with a simple string
void chatterCallback(const std_msgs::String::ConstPtr& msg)
// void chatterCallback(const std_msgs::String msg)
{
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

    ros::spin();

    return 0;
}
