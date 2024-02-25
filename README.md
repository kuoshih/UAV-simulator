# UAV-simulator

![alt text](https://github.com/Hypha-ROS/hypharos_minibot/blob/master/document/gazebo.png)  

## Abstract
This code is for MA3137 Special Topics in Robotics.
It is a sample code for a drone to take-off and fly to destinations.
This code activate a node "main" and the other sensor nodes. 
Main node publish the topics -- mavros/setpoint_position/local. 

## Virtual box image file
To be uploaded.

## About us

Developer:   
* Kuo-Shih Tseng   
Contact: kuoshih@math.ncu.edu.tw   
Date: 2024/02/25  

## Compile the code
$ cd catkin_ws/src  
$ git clone https://github.com/kuoshih/UAV-simulator   
$ cd ..  
$ catkin_make  

Or Download this this code to ~\catkin_ws\src.   
Unzip UAV-Simulator.zip to replace the original code.
  
$cd catkin_ws  
$catkin_make  

## Run the code   
1st terminal:
You have to run the gazebo first.
$roslaunch px4 mavros_posix_sitl.launch 
2nd terminal:
Once you have a drone in the gazebo simulator, you can run the sample code.
$ cd ~\catkin_ws\src\UAV\src
$ rosrun UAV main


## Edit code  
You can edit src/main.cpp for your project.

