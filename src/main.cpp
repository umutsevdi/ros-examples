#define __ROS_VERSION__ "3"
#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>

int main(int argc, char** argv) {
    /* code */
    std::cout << "/* message */" __ROS_VERSION__ << std::endl;
    ros::init(argc, argv, "basics_writer");
    std::cout << "/* <> */" << std::endl;
    ros::NodeHandle handler;

    ros::Publisher publisher = handler.advertise<std_msgs::String>("topic", 1000);
    ros::Rate loop_rate(1);
    int index;
    while (ros::ok()) {
        std_msgs::String msg;
        std::stringstream stream;

        stream << "log " << index++ << " | input message";
        msg.data = stream.str();
        std::cout << "WRITER " << ros::this_node::getName() << ":: " + msg.data << std::endl;

        publisher.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }

}