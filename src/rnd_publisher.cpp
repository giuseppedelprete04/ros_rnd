#include "ros/ros.h"
#include "ros_rnd/rnd_num.h"
#include <cstdlib>
#include <iostream>

//The first publisher publish two random numbers 
class ROS_PUB1 {

	private:
		ros::NodeHandle nh;
		ros::Publisher topic_pub;	

	public:
		ROS_PUB1();
		float send_msg();
	
};

ROS_PUB1::ROS_PUB1() {
	topic_pub = nh.advertise<ros_rnd::rnd_num>("rnd_num",10);
}



float ROS_PUB1::send_msg() {
	float a = rand() % 10;
	float b = rand() % 10;
	ros_rnd::rnd_num msg;
	msg.num1 = a;
	msg.num2 = b;
	ROS_INFO("Numbers: %f - %f\n", msg.num1, msg.num2);
	topic_pub.publish(msg);
}


//The second publisher publish the sum of two numbers 

class ROS_PUB2 {

	private:
		ros::NodeHandle nh;
		ros::Publisher topic_pub;
	public:
		ROS_PUB2();
                float send_msg(float a, float b);
};

ROS_PUB2::ROS_PUB2() {
	topic_pub = nh.advertise<ros_rnd::rnd_num >("sum",10);
}

float ROS_PUB2::send_msg(float a, float b) {
  ros_rnd::rnd_num msg;
  msg.num1 = a;
  msg.num2 = b;
  msg.sum = a+b;
  ROS_INFO("Sum: %f + %f = %f\n", msg.num1,msg.num2,msg.sum);
  topic_pub.publish(msg);
}

//The first subscriber takes the numbers from the first publisher and calculate the sum
class ROS_SUB1 {
	private:
		ros::NodeHandle _nh;
		ros::Subscriber _topic_sub;
	        ROS_PUB2 sum_pub2;
	public:
		ROS_SUB1();
		void topic_cb(ros_rnd::rnd_numConstPtr data);
};

ROS_SUB1::ROS_SUB1() {
	_topic_sub = _nh.subscribe("rnd_num",0,&ROS_SUB1::topic_cb,this);
}

void ROS_SUB1::topic_cb(ros_rnd::rnd_numConstPtr data) {
	float sum = data->num1 + data->num2;
	sum_pub2.send_msg(data->num1, data->num2);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "ros_rnd_num");
  ROS_PUB1 pub1;
  ROS_SUB1 sub1;

	ros::Rate rate(1);

	while ( ros::ok() ) {
		pub1.send_msg();
		rate.sleep();
    ros::spinOnce();
    printf("\n");
	}

  return 0;
}
