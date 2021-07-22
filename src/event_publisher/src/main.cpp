#include <ros/ros.h>
#include <std_msgs/String.h>

// opencv
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

// messages
#include <dvs_msgs/Event.h>
#include <dvs_msgs/EventArray.h>
#include "Event.h"

// file manager
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


int main(int argc, char **argv)
{

    ros::init(argc, argv, "event_publisher");

    ros::NodeHandle nh_private("~");

    std::string filename = "filename";
    std::string yaml = "yaml";
    nh_private.param<std::string>("filename", filename, "");
    nh_private.param<std::string>("yaml", yaml, "");

    ros::Publisher event_array_pub = nh_private.advertise<dvs_msgs::EventArray>("/events", 0);
    

    Event event(yaml);

    ROS_INFO("Reading event data");
    event.eventReader(filename);

    event.setEventPublisher(&event_array_pub);
    
    ROS_INFO("Begin to publish data");
    event.publish();

    ROS_INFO("Finish publishing data");
    
    return 0;
}