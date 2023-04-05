/******************************************************************************
 * File: basics/listener.cpp
 *
 * Author: Umut Sevdi
 * Created: 04/05/23
 * Description: In this example a listener with the frequency of one listens
 * the topic and pushes all incoming messages into a stack.
 * - Every 10 seconds collector captures all elements in the stack, and pushes
 *  all of them in JSON format.
 * *****************************************************************************/
#define __ROS_VERSION__ "4"
#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>
#include <thread>

 /**
  * collect - Displays the incoming message and pushes into a stack
 */
void collect(const std_msgs::String::ConstPtr& msg);

std::vector<std::string> stack;

int main(int argc, char** argv) {
    ros::init(argc, argv, "basics_listener");
    ROS_INFO("Started listener thread");
    ros::NodeHandle handler;

    ros::Subscriber subscriber = handler
        .subscribe<std_msgs::String>("topic", 1000, collect);
    ros::Publisher collector = handler.advertise<std_msgs::String>("collector", 2000);

    std::thread t([collector]() {
        ROS_INFO("Started collector thread");
        ros::Rate loop_rate(0.1);
        while (ros::ok()) {
            std::stringstream s;
            s << "[";
            while (!stack.empty()) {
                std::string& msg = stack.back();
                s << msg << ", ";
                stack.pop_back();
            }
            s << "\n]";
            std_msgs::String m;
            m.data = s.str();
            if (m.data != "[\n]") {
                collector.publish(m);
            }
            ros::spinOnce();
            loop_rate.sleep();
        }
        });
    ros::spin();
}

void collect(const std_msgs::String::ConstPtr& msg) {
    stack.push_back(msg->data);
    std::cout << "LISTENER " << msg->data << stack.empty() << std::endl;
}

