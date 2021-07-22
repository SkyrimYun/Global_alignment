#include "Event.h"

Event::Event(std::string yaml)
{
    msg = dvs_msgs::EventArrayPtr(new dvs_msgs::EventArray());
  
    next_send_time = 0.0;

    // read yaml file
    cv::FileStorage fSettings(yaml, cv::FileStorage::READ);
    if (!fSettings.isOpened())
    {
        throw std::runtime_error(std::string("Could not open file: ") + yaml);
    }

    height = fSettings["height"];
    width = fSettings["width"];

    delta_time = fSettings["Event.delta_time"];
    max_events = fSettings["Event.max_event"];

}

Event::~Event(){
}

void Event::eventReader(const std::string &filename)
{
    std::vector<dvs_msgs::Event> Data;
    std::string file_;
    file_.append(filename);
    file_.append("/events.txt");

    std::ifstream openFile(file_.c_str());
    if (!openFile.is_open())
    {
        std::cout << "text file open error" << std::endl;
    }
    else
    {
        std::string line;
        std::string token;
        std::vector<std::string> vToken;
        char *sz;

        while (getline(openFile, line))
        {
            dvs_msgs::Event msg;
            std::stringstream ss(line);
            while (ss>>token)
                vToken.push_back(token);

            if (vToken.size() == 4)
            {
                msg.ts = ros::Time(std::strtod(vToken[0].c_str(), &sz));
                msg.x = uint32_t(std::strtod(vToken[1].c_str(), &sz));
                msg.y = uint32_t(std::strtod(vToken[2].c_str(), &sz));
                msg.polarity = uint8_t(std::strtod(vToken[3].c_str(), &sz));

                // std::cout << "EVT::  "<< vToken[0]<< ",  "<< vToken[1]<< ",  "<< vToken[2]<< ",  "<< vToken[3] << std::endl;
                Data.push_back(msg);
            }
            vToken.clear();
        }
        openFile.close();
    }
    this->eventData = Data;
    std::cout << "event data size: " << eventData.size() << std::endl;
}

void Event::publish()
{
    int count = 0;
    long iterator = 0;
    while(iterator < eventData.size()-1)
    {
        msg = dvs_msgs::EventArrayPtr(new dvs_msgs::EventArray());
        count++;
        msg->height = height;
        msg->width = width;
        double init_time = eventData.at(iterator).ts.toSec();
        while (eventData.at(iterator).ts.toSec() - init_time <= delta_time && msg->events.size() < max_events && iterator < eventData.size()-1)
        {
            msg->events.push_back(eventData.at(iterator));
            msg->header.seq = seq++;
            msg->header.stamp = eventData.at(iterator).ts;
            iterator++;
        }
        std::cout << count << " msg dur: " << msg->events.back().ts.toSec() - msg->events.front().ts.toSec() << "; msg size: " << msg->events.size() << std::endl;
        this->event_array_pub->publish(msg);
    }
}


void Event::setEventPublisher(ros::Publisher *pub){
    this->event_array_pub = pub;
}

