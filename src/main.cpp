/**
 * @file offb_node.cpp
 * @brief offboard example node, written with mavros version 0.14.2, px4 flight
 * stack and tested in Gazebo SITL
 */

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <sensor_msgs/Image.h>
#include <cstring>
#define FLIGHT_ALTITUDE 1.5f

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

void depthImageCallback(const sensor_msgs::Image::ConstPtr& msg)
{
    // 計算影像的中心像素位置
    int centerX = msg->width / 2;
    int centerY = msg->height / 2;

    // 計算中心像素在資料中的索引
    int index = (centerY * msg->width) + centerX;

    // 檢查索引是否在有效範圍內
    if (index >= 0 && index < msg->width * msg->height)
    {
        // 使用memcpy從影像資料中提取深度值
        float depth1;
        memcpy(&depth1, &msg->data[index * sizeof(float)], sizeof(float));
        
        // 在這裡你可以對深度值進行任何需要的處理
        ROS_INFO("Depth at center pixel: %f", depth1);
    }
    else
    {
        ROS_WARN("Center pixel index out of bounds.");
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, state_cb);
    ros::Subscriber sub = nh.subscribe("/camera/depth/image_raw", 1, depthImageCallback);

    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            ("mavros/cmd/arming");
    ros::ServiceClient land_client = nh.serviceClient<mavros_msgs::CommandTOL>
      ("mavros/cmd/land");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            ("mavros/set_mode");

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok() && current_state.connected){
        ros::spinOnce();
        rate.sleep();
        ROS_INFO("connecting to FCT...");
    }

    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = FLIGHT_ALTITUDE;

    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    mavros_msgs::CommandTOL land_cmd;
    land_cmd.request.yaw = 0;
    land_cmd.request.latitude = 0;
    land_cmd.request.longitude = 0;
    land_cmd.request.altitude = 0;

    ros::Time last_request = ros::Time::now();

    // change to offboard mode and arm
    while(ros::ok() && !current_state.armed){
        if( current_state.mode != "OFFBOARD" &&
            (ros::Time::now() - last_request > ros::Duration(5.0))){
          ROS_INFO(current_state.mode.c_str());
            if( set_mode_client.call(offb_set_mode) &&
                offb_set_mode.response.mode_sent){
                ROS_INFO("Offboard enabled");
            }
            last_request = ros::Time::now();
        } else {
            if( !current_state.armed &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){
                if( arming_client.call(arm_cmd) &&
                    arm_cmd.response.success){
                    ROS_INFO("Vehicle armed");
                }
                last_request = ros::Time::now();
            }
        }
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    // go to the first waypoint
    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = FLIGHT_ALTITUDE;

    ROS_INFO("going to the first way point");
    for(int i = 0; ros::ok() && i < 10*20; ++i){
      local_pos_pub.publish(pose);
      ros::spinOnce();
      rate.sleep();
    }
    ROS_INFO("first way point finished!");

    ROS_INFO("tring to land");
    while (!(land_client.call(land_cmd) &&
            land_cmd.response.success)){
      //local_pos_pub.publish(pose);
      ROS_INFO("tring to land");
      ros::spinOnce();
      rate.sleep();
    }
    return 0;
}
