// class for Event
#ifndef __EVENT_H__
#define __EVENT_H__

// ros
#include <ros/ros.h>

// opencv
#include <opencv2/core.hpp>
#include <cv_bridge/cv_bridge.h>

// messages
#include <dvs_msgs/Event.h>
#include <dvs_msgs/EventArray.h>

// file manager
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
// general
#include <string>

class Event{
private:
    std::vector< dvs_msgs::Event > eventData;

    //temporay image
 
    dvs_msgs::EventArrayPtr msg;
    
public:
    Event(std::string yaml);
    ~Event();

    //functions
    void eventReader(const std::string &filename);
    void publish();



    void setEventPublisher(ros::Publisher *pub);
   

    ros::Publisher* event_array_pub;


    //variables
    int height, width;

    uint32_t seq;

    double delta_time;
    double next_send_time;
    int max_events;
};

#endif //__EVENT_H__