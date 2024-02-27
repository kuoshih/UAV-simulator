# UAV-simulator

![alt text](https://github.com/kuoshih/UAV-simulator/blob/main/documents/gazebo.png)  


## Abstract
This code is for MA3137 Special Topics in Robotics.
It is a sample code for a drone to take-off and fly to destinations.
This code activate a node "main" and the other sensor nodes. 
Main node publish the topics -- mavros/setpoint_position/local. 

## Virtual box image file
1. Install virtual box: https://www.virtualbox.org/ (or Google：Virtualbox)  
2. Download the image file: https://drive.google.com/file/d/1qFrtBpMbufIv_EWJFTQMAEwfulgCMK3J/view?usp=sharing  
3. import the OVA file (see https://www.youtube.com/watch?v=7GbPbaMwlKw)  
account: hypharos  
pw: hypharos  
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

## FAQ  
1. Network error of the virtualbox?   
Since your network hardware is different, you have to set the etherent and wirless hardware.   
![alt text](https://github.com/kuoshih/UAV-simulator/blob/main/documents/network_error.png)  
