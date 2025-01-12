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
#include "tutorial_interfaces/msg/weather.hpp"  

using std::placeholders::_1;

class WeatherSubscriber : public rclcpp::Node
{
public:
  WeatherSubscriber()
  : Node("weather_subscriber")
  {
    subscription_ = this->create_subscription<tutorial_interfaces::msg::Weather>(
      "Weather", 10, std::bind(&WeatherSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const tutorial_interfaces::msg::Weather & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "Temperature is %ld", msg.temperature);
    if (msg.windy) { 
      RCLCPP_INFO(this->get_logger(), "Move the plants since it is windy");
    } 
    if (msg.temperature > 25) { 
      RCLCPP_INFO(this->get_logger(), "It is hot. Take the trash out.");
    }
    if (msg.sunny) { 
      RCLCPP_INFO(this->get_logger(), "It is sunny. Do the laundry.");
    } 
  }
  rclcpp::Subscription<tutorial_interfaces::msg::Weather>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<WeatherSubscriber>());
  rclcpp::shutdown();
  return 0;
}
