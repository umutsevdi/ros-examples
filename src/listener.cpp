#define __ROS_VERSION__ "4"
#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>

#include <functional>
void default_callback(const std_msgs::String::ConstPtr& msg);

int main(int argc, char** argv) {
    /* code */
    std::cout << "/* message */" __ROS_VERSION__ << std::endl;
    ros::init(argc, argv, "basics_listener");
    std::cout << "/* <> */" << std::endl;
    ros::NodeHandle handler;

    ros::Subscriber subscriber = handler
        .subscribe<std_msgs::String>("topic", 1000, default_callback);
    ros::Rate loop_rate(1);
    ros::spin();

}

void default_callback(const std_msgs::String::ConstPtr& msg) {
    std::cout << "LISTENER " << ros::this_node::getName() << ":: " + msg->data << std::endl;
}