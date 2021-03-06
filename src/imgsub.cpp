#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

void imageSubCallback(const sensor_msgs::ImageConstPtr& msg)
{
  cv::Mat img;
  try
  {

    img = cv_bridge::toCvShare(msg, "bgr8")->image;
    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
    cv::imshow("view", img);
    cv::waitKey(30);

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_ipm");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");

  std::string sub_topic;
  pnh.param<std::string>("sub_topic", sub_topic, "usb_cam/image_raw"); 

  cv::namedWindow("view");

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe(sub_topic, 1, imageSubCallback);
  ros::spin();
  cv::destroyWindow("view");
}