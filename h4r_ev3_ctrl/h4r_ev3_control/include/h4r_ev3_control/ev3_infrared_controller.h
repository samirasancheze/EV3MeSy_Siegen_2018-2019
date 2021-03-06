/*
 * This file (ev3_infrared_controller.h) is part of h4r_ev3_control.
 * Date: 06.01.2016
 *
 * Author: Christian Holl
 * http://github.com/Hacks4ROS
 *
 * h4r_ev3_control is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * h4r_ev3_control is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with h4r_ev3_control.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef EV3_INFRARED_CONTROLLER_H_
#define EV3_INFRARED_CONTROLLER_H_

#include <controller_interface/controller.h>
#include <pluginlib/class_list_macros.h>
#include <realtime_tools/realtime_publisher.h>
#include <boost/shared_ptr.hpp>
#include <sensor_msgs/Range.h>
#include <sensor_msgs/Joy.h>
#include <h4r_ev3_msgs/Seek.h>
#include <limits>

#include <h4r_ev3_control/Ev3SensorInterface.h>

namespace ev3_control
{

/**
 * \page Ev3InfraredController Ev3InfraredController
 * \ingroup Ev3Controllers
 * \image html EV3Infrared.png
 * \section Controller Function
 * This controller is used to read the standard EV3 Infrared Sensor
 *
 * \example infrared.launch
 * \example infrared.yaml
 */

/**
 * \ingroup Ev3Controllers
 */
class Ev3InfraredController: public controller_interface::Controller<
		Ev3SensorInterface>
{
private:
	std::string port_;
	Ev3Strings::Ev3InfraredMode mode_;
	Ev3SensorHandle handle_;
	H4REv3IRSensorSpecIface ir_interface_;
	bool sensor_mode_needs_init_;

	double max_range_;
	double min_range_;
	std::string frame_id_;
	unsigned value_number_;

	//Range Publisher
	typedef boost::shared_ptr<
			realtime_tools::RealtimePublisher<sensor_msgs::Range> > RtRangePublisherPtr;
	RtRangePublisherPtr realtime_range_publisher_;

	typedef boost::shared_ptr<
			realtime_tools::RealtimePublisher<h4r_ev3_msgs::Seek> > RtSeekPublisherPtr;
	RtSeekPublisherPtr realtime_seek_publishers_[4];

	typedef boost::shared_ptr<
			realtime_tools::RealtimePublisher<sensor_msgs::Joy> > RtJoyPublisherPtr;
	RtJoyPublisherPtr realtime_joy_publishers_[4];


	ros::Time last_publish_time_[4];
	double publish_rate_;
	bool first_time_[4];

public:
	Ev3InfraredController();
	virtual ~Ev3InfraredController();

	virtual bool init(Ev3SensorInterface* hw,
			ros::NodeHandle &root_nh,
			ros::NodeHandle& ctrl_nh);

	virtual void starting(const ros::Time& time);
	virtual void update(const ros::Time& time, const ros::Duration& /*period*/);
	virtual void stopping(const ros::Time& /*time*/){}

};

} /* namespace ev3_control */

#endif /* EV3_INFRARED_CONTROLLER_H_ */
