// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "tutorial_interfaces/msg/weather.hpp"  

using std::placeholders::_1;

class MultiSubscriber : public rclcpp::Node
{
public:
  MultiSubscriber()
  : Node("multi_subscriber") 
  {
    subscription_weather_ = this->create_subscription<tutorial_interfaces::msg::Weather>(
      "Weather", 10, std::bind(&MultiSubscriber::weather_callback, this, _1));
    subscription_travel_ = this->create_subscription<std_msgs::msg::Bool>(
      "Travel", 10, std::bind(&MultiSubscriber::travel_callback, this, _1));  
  }

private:
  void weather_callback(const tutorial_interfaces::msg::Weather & msg) 
  { 
    want_hike_ = false;
    if (!msg.rain && !msg.snow && !wet_[0] && !wet_[1]) {
      RCLCPP_INFO(this->get_logger(), "No rain or snow past three days. Go hiking");
      want_hike_ = true;
    }
    else if (msg.snow) {
      RCLCPP_INFO(this->get_logger(), "Do you want to build a snowman?");
    } else if (msg.temperature > 25) { 
      RCLCPP_INFO(this->get_logger(), "We go swimming in the lake.");
    } else {
      RCLCPP_INFO(this->get_logger(), "We take a walk.");  
    }
    // Overwrites into wet_ info of 3 days ago. Each time writes into an alternating index. 
    wet_[(int)day_++ % 2] = msg.rain || msg.snow ;
  }
  void travel_callback(const std_msgs::msg::Bool & msg) 
  { 
    if (!want_hike_) {return;}

    if (msg.data) { 
      RCLCPP_INFO(this->get_logger(), "There is a good deal for travel. Climb Mattehorn.");
    } else { 
      RCLCPP_INFO(this->get_logger(), "It is expensive to travel. Climb Uetliberg.");
    } 
    want_hike_=false;
  }
  bool want_hike_ = false;
  bool wet_[2] = {true, true}; // stores if it snowed or rained yesterday and the day before.
  rclcpp::Subscription<tutorial_interfaces::msg::Weather>::SharedPtr subscription_weather_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription_travel_; 
  size_t day_ = 0;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv); 
  rclcpp::spin(std::make_shared<MultiSubscriber>());
  rclcpp::shutdown();
  return 0;
}
