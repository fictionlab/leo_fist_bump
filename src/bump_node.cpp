#include <ros/ros.h>
#include <std_msgs/Time.h>
#include <std_msgs/Float32.h>


// This code makes the Leo Rover lift one of its wheels - the one on the front, on the right. No other. It's hard-coded.
// Also, it may not work. You need a pretty grippy surface for this thing to work as intended. 
// No additional weight on the rover might help. Good luck.

// Send this message when the rover (and this node) are running to lift the wheel:
// rostopic pub cmd_bump std_msgs/Time "data:
// secs: 0
// nsecs: 750000000"

// Send a similar one, with a random time, to lower the wheel.

// You can make the wheel bounce up and down using:
// rostopic pub -r 1 cmd_bump std_msgs/Time "data:
// secs: 0
// nsecs: 750000000"


ros::Subscriber sub;

ros::Publisher pub_RR_pwm;
ros::Publisher pub_RR_vel;

ros::Publisher pub_RL_vel;
ros::Publisher pub_FR_vel;
ros::Publisher pub_FL_vel;

std_msgs::Time timeMsg;
std_msgs::Float32 floatMsg;

bool up = false;

ros::Time start;

void control_not_moving_wheels(std_msgs::Float32 message){
    
    pub_RL_vel.publish(message);
    pub_FR_vel.publish(message);
    pub_FL_vel.publish(message);
}

void bump_callback(const std_msgs::Time::ConstPtr& msg){

    start = ros::Time::now();

    ros::Duration timeToMove(msg->data.sec,msg->data.nsec);

    if(up){
        // Get rid of the torque holding the wheel up
        floatMsg.data = 0;
        pub_RR_pwm.publish(floatMsg);
        control_not_moving_wheels(floatMsg);
        up = false;
    }
    else if(!up){
        // Force RR wheel to move as fast and hard as possible 
        floatMsg.data = 100.0;
        pub_RR_pwm.publish(floatMsg);
        // Force all the other wheels to move with an isignificant speed - prevents the rover from slipping
        floatMsg.data = -0.01;
        control_not_moving_wheels(floatMsg);
        up = true;

        while(ros::Time::now() - start < timeToMove){
        // wait for the chosen duration to give the wheel enough time to raise or lower itself
        }

        // Force all the wheels to move with really low speed - prevents the rover from losing torque
        // and dropping the wheel because of that. 
        floatMsg.data = 0.001;
        pub_RR_vel.publish(floatMsg);
        control_not_moving_wheels(floatMsg);    
        }
    
}

int main(int argc, char **argv){

    ros::init(argc, argv, "bump_node");
    ros::NodeHandle nh;

    pub_RR_pwm = nh.advertise<std_msgs::Float32>("firmware/wheel_RR/cmd_pwm_duty", 1000);
    pub_RR_vel = nh.advertise<std_msgs::Float32>("firmware/wheel_RR/cmd_velocity", 1000);
    pub_RL_vel = nh.advertise<std_msgs::Float32>("firmware/wheel_RL/cmd_velocity", 1000);
    pub_FR_vel = nh.advertise<std_msgs::Float32>("firmware/wheel_FR/cmd_velocity", 1000);
    pub_FL_vel = nh.advertise<std_msgs::Float32>("firmware/wheel_FL/cmd_velocity", 1000); 

    sub = nh.subscribe("cmd_bump", 1000, bump_callback);

    while (ros::ok())
    {
        ros::spinOnce();
    }
}



