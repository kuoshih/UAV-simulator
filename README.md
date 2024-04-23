# UAV-simulator

![alt text](https://github.com/kuoshih/UAV-simulator/blob/main/documents/gazebo.png)  


## Abstract
This repo is for MA3137 Special Topics in Robotics which is a sample code for a drone to take-off and fly to destinations.
This code activates a node "main" and other sensor nodes.
The main node publishs the topic: -- mavros/setpoint_position/local. 

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
```
$ cd catkin_ws/src  
$ git clone https://github.com/kuoshih/UAV-simulator   
$ cd ..  
$ catkin_make  
```

*If an error occured saying
```
Multiple packages found with the same name "UAV":
- UAV
- UAV-simulator
```
Delete the old "UAV" folder in ~/catkin_ws/src.

**If an error about the PX4 package occured, simply move it out of the folder, then put it back after the `catkin_make` excecution.

Or you can download UAV-Simulator.zip and unzip it to ~\catkin_ws\src.
Then, manually replace the original "UAV" folder, then execute `catkin_make`.

## Run the code   
1st terminal:  
Run Gazebo using roslaunch  
```
$ roslaunch px4 mavros_posix_sitl.launch
```
  
2nd terminal:  
Once you successfully open Gazebo and a drone is loaded, you can run the sample code.  
``` 
$ rosrun UAV main  
```

## Edit code  
You can edit src/main.cpp for your project.

## FAQ  
1. Network error of the virtualbox?   
Since your network hardware is different, you have to set the etherent and wirless hardware.   
![alt text](https://github.com/kuoshih/UAV-simulator/blob/main/documents/network_error.png)  
