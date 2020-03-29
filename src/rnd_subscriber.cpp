#include "ros/ros.h"
#include "ros_rnd/rnd_num.h"
#include <cstdlib>
#include <iostream>

class ROS_SUB2 {
	public:
		ROS_SUB2();
		void topic_cb( ros_rnd::rnd_numConstPtr data );

	private:
		ros::NodeHandle _nh;
		ros::Subscriber _topic_sub;
};

ROS_SUB2::ROS_SUB2() {
	_topic_sub = _nh.subscribe( "sum", 0, &ROS_SUB2::topic_cb, this );
}

void ROS_SUB2::topic_cb( ros_rnd::rnd_numConstPtr data ) {
	ROS_INFO( "Numbers: %f + %f = %f\n", data->num1, data->num2, data->sum );
}

int main( int argc, char** argv ) {
	ros::init(argc,argv,"ros_sum");
	ROS_SUB2 sub2;
	ros::spin();
	return 0;
}
