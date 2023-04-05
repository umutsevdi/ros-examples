/******************************************************************************
 * File: basics/main.cpp
 *
 * Author: Umut Sevdi
 * Created: 04/05/23
 * Description: Simple publisher example, shares a string message in constant
 * rate
 * *****************************************************************************/
#define __ROS_VERSION__ "3"
#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>

int main(int argc, char** argv) {
    ROS_INFO("Started publisher thread thread");
    ros::init(argc, argv, "basics_writer");
    ros::NodeHandle handler;

    ros::Publisher publisher =
        handler.advertise<std_msgs::String>("topic", 1000);
    ros::Rate loop_rate(1);
    int index;
    while (ros::ok()) {
        std_msgs::String msg;
        std::stringstream stream;

        stream << "{ \"index\": " << index++ \
            << ", \"name\": " << \
            ros::this_node::getName() << " }";
        msg.data = stream.str();
        std::cout << "WRITER#" + msg.data << std::endl;
        publisher.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

}